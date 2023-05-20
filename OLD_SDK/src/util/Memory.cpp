#include "util/Memory.hpp"

#include <vector>
#include <cstring>

#ifdef _WIN32
	#include <tchar.h>
	#include <windows.h>
	// Last
	#include <psapi.h>
#else
	#include <cstdint>
	#include <dlfcn.h>
	#include <link.h>
	#include <sys/uio.h>
	#include <unistd.h>
	#include <cstring>
	#include <sys/mman.h>
#endif

#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x, '0', '9') ? x - '0' : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

std::vector<Memory::ModuleInfo> Memory::moduleList;

auto Memory::TryGetModule(const char* moduleName, Memory::ModuleInfo* info) -> bool {
    if ( Memory::moduleList.empty() ) {
		#ifdef _WIN32
	        HMODULE hMods[1024];
	        HANDLE pHandle = GetCurrentProcess();
	        DWORD cbNeeded;
	        if (EnumProcessModules(pHandle, hMods, sizeof(hMods), &cbNeeded)) {
	            for (unsigned i = 0; i < (cbNeeded / sizeof(HMODULE)); ++i) {
	                char buffer[MAX_PATH];
	                if (!GetModuleFileName(hMods[i], buffer, sizeof(buffer)))
	                    continue;

	                auto modinfo = MODULEINFO();
	                if (!GetModuleInformation(pHandle, hMods[i], &modinfo, sizeof(modinfo)))
	                    continue;

	                auto module = ModuleInfo();

	                auto temp = std::string(buffer);
	                auto index = temp.find_last_of("\\/");
	                temp = temp.substr(index + 1, temp.length() - index);

	                snprintf(module.name, sizeof(module.name), "%s", temp.c_str());
	                module.base = (uintptr_t)modinfo.lpBaseOfDll;
	                module.size = (uintptr_t)modinfo.SizeOfImage;
	                snprintf(module.path, sizeof(module.path), "%s", buffer);

	                Memory::moduleList.push_back(module);
	            }
	        }

		#else
            dl_iterate_phdr(
				[](struct dl_phdr_info* info, size_t, void*) {
		            auto module = Memory::ModuleInfo();

		            std::string temp = std::string(info->dlpi_name);
		            int index = temp.find_last_of("\\/");
		            temp = temp.substr(index + 1, temp.length() - index);
		            snprintf(module.name, sizeof(module.name), "%s", temp.c_str());

		            module.base = info->dlpi_addr + info->dlpi_phdr[0].p_paddr;
		            module.size = info->dlpi_phdr[0].p_memsz;
		            strcpy(module.path, info->dlpi_name);

		            Memory::moduleList.push_back(module);
		            return 0;
	            },
				nullptr
			);
		#endif
    }

    for ( Memory::ModuleInfo& item : Memory::moduleList ) {
        if (! std::strcmp(item.name, moduleName) ) {
            if ( info ) {
                *info = item;
            }
            return true;
        }
    }

    return false;
}

auto Memory::GetModulePath(const char* moduleName) -> const char* {
    auto info = Memory::ModuleInfo();
    return ( Memory::TryGetModule(moduleName, &info) ) ? std::string(info.path).c_str() : nullptr;
}

auto Memory::GetModuleHandleByName(const char* moduleName) -> void* {
    auto info = Memory::ModuleInfo();
	#ifdef _WIN32
	    return ( Memory::TryGetModule(moduleName, &info) ) ? GetModuleHandleA(info.path) : nullptr;
	#else
	    return ( TryGetModule(moduleName, &info) ) ? dlopen(info.path, RTLD_NOLOAD | RTLD_NOW) : nullptr;
	#endif
}

auto Memory::CloseModuleHandle(void* moduleHandle) -> void {
	#ifndef _WIN32
	    dlclose(moduleHandle);
	#endif
}

auto Memory::GetProcessName() -> std::string {
	#ifdef _WIN32
	    char temp[MAX_PATH];
	    GetModuleFileName( NULL, temp, sizeof(temp) );
	#else
	    char link[32];
	    char temp[MAX_PATH] = { 0 };
	    sprintf(link, "/proc/%d/exe", getpid());
	    readlink(link, temp, sizeof(temp));
	#endif

    auto proc = std::string(temp);
    auto index = proc.find_last_of("\\/");
    proc = proc.substr( index + 1, proc.length() - index );

    return proc;
}

auto Memory::FindAddress( const uintptr_t start, const uintptr_t end, const char* target ) -> uintptr_t {
    const char* pattern = target;
    uintptr_t result = 0;

    for ( auto position = start; position < end; ++position ) {
        if (! *pattern )
            return result;

        auto match = *reinterpret_cast<const uint8_t*>(pattern);
        auto byte = *reinterpret_cast<const uint8_t*>(position);

        if (match == '\?' || byte == getByte(pattern)) {
            if (!result)
                result = position;

            if (!pattern[2])
                return result;

            pattern += (match != '\?') ? 3 : 2;
        } else {
            pattern = target;
            result = 0;
        }
    }
    return 0;
}

auto Memory::Scan(const char* moduleName, const char* pattern, int offset) -> uintptr_t {
    uintptr_t result = 0;

    auto info = Memory::ModuleInfo();
    if ( Memory::TryGetModule(moduleName, &info) ) {
        auto start = uintptr_t(info.base);
        auto end = start + info.size;
        result = FindAddress(start, end, pattern);
        if ( result ) {
            result += offset;
        }
    }
    return result;
}

auto Memory::PatchString(uintptr_t address, const char* chars, int size) -> void {
	#ifdef _WIN32
	    DWORD old;
	    VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &old);
	    memcpy((LPVOID)address, chars, size);
	    VirtualProtect((LPVOID)address, size, old, nullptr);
	#else
		auto startPage = (uintptr_t)address & 0xFFFFF000;
		uintptr_t endPage = ((uintptr_t)address + size) & 0xFFFFF000;
		uintptr_t pageLen = endPage - startPage + 0x1000;
		mprotect((void*)startPage, pageLen, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif
}

#ifdef _WIN32
	Memory::Patch::~Patch() {
	    if (this->original) {
	        this->Restore();
	        delete this->original;
	        this->original = nullptr;
	    }
	}

	auto Memory::Patch::Execute(uintptr_t loc, unsigned char* bytes) -> bool {
	    this->location = loc;
	    this->size = sizeof(bytes) / sizeof(bytes[0]) - 1;
	    this->original = new unsigned char[this->size];

	    for ( size_t i = 0; i < this->size; i++ ) {
	        if (!
				ReadProcessMemory(
					GetCurrentProcess(),
	                reinterpret_cast<LPVOID>( this->location + i ),
	                &this->original[i],
	                1,
	                0
				)
			) { return false; }
	    }

	    for ( size_t i = 0; i < this->size; i++ ) {
	        if (!
				WriteProcessMemory(
					GetCurrentProcess(),
	                reinterpret_cast<LPVOID>( this->location + i ),
	                &bytes[i],
	                1,
	                0
				)
			) { return false; }
	    }
	    return true;
	}

	auto Memory::Patch::Restore() -> bool {
	    if ( this->location && this->original ) {
	        for ( size_t i = 0; i < this->size; i++ ) {
	            if (!
					WriteProcessMemory(
						GetCurrentProcess(),
	                    reinterpret_cast<LPVOID>(this->location + i),
	                    &this->original[i],
	                    1,
	                    0
					)
				) { return false; }
	        }
	        return true;
	    }
	    return false;
	}
#endif
