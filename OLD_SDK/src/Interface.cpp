#include <cstring>
#include "Interface.hpp"
#include "module/Console.hpp"
#include "engine/Interface.hpp"

#ifdef _WIN32
    #define CreateInterfaceInternal_Offset 5
	#define s_pInterfaceRegs_Offset 6
#else
    #define CreateInterfaceInternal_Offset 1
#endif

Interface::Interface()
    : baseclass(nullptr)
    , vtable(nullptr)
    , vtableSize(0)
    , isHooked(false)
    , copy(nullptr) { }

Interface::Interface(void* baseclass, bool copyVtable, bool autoHook) : Interface() {
    this->baseclass = reinterpret_cast<uintptr_t**>(baseclass);
    this->vtable = *this->baseclass;

    while ( this->vtable[this->vtableSize] ) {
        ++this->vtableSize;
    }

    if ( copyVtable ) {
        this->CopyVtable();
        if (autoHook) {
            this->EnableHooks();
        }
    }
}

Interface::~Interface() {
    this->DisableHooks();
    if (this->copy) {
        this->copy.reset();
    }
}

auto Interface::CopyVtable() -> void {
    if (! this->copy ) {
        this->copy = std::make_unique<uintptr_t[]>(this->vtableSize +1);
        std::memcpy(this->copy.get(), this->vtable - 1, sizeof(uintptr_t) + this->vtableSize * sizeof(uintptr_t));
    }
}

auto Interface::EnableHooks() -> void {
    if (! this->isHooked ) {
        *this->baseclass = this->copy.get() + 1;
        this->isHooked = true;
    }
}

auto Interface::DisableHooks() -> void {
    if ( this->isHooked ) {
        *this->baseclass = this->vtable;
        this->isHooked = false;
    }
}

auto Interface::Unhook(int index) -> bool {
    if ( index >= 0 && index < this->vtableSize ) {
        this->copy[index + 1] = this->vtable[index];
        return true;
    }
    return false;
}

auto Interface::Create(void* ptr, bool copyVtable, bool autoHook) -> Interface* {
    return (ptr) ? new Interface(ptr, copyVtable, autoHook) : nullptr;
}

auto Interface::Create(const char* filename, const char* interfaceSymbol, bool copyVtable, bool autoHook) -> Interface* {
    auto ptr = Interface::GetPtr(filename, interfaceSymbol);
    return (ptr) ? new Interface(ptr, copyVtable, autoHook) : nullptr;
}

auto Interface::Delete(Interface* ptr) -> void {
    if ( ptr ) {
        delete ptr;
        ptr = nullptr;
    }
}

void* Interface::GetPtr(const char* filename, const char* interfaceSymbol) {
    auto handle = Memory::GetModuleHandleByName(filename);
    if (! handle ) {
        console->DevWarning("Portal 2 SDK: Failed to open module %s!\n", filename);
        return nullptr;
    }

    auto CreateInterface = Memory::GetSymbolAddress(handle, "CreateInterface");
    Memory::CloseModuleHandle(handle);

    if (! CreateInterface ) {
        console->DevWarning("Portal 2 SDK: Failed to find symbol CreateInterface for %s!\n", filename);
        return nullptr;
    }

    auto CreateInterfaceInternal = Memory::Read( (uintptr_t) CreateInterface + CreateInterfaceInternal_Offset );
    #ifdef _WIN32
        auto s_pInterfaceRegs = **reinterpret_cast<InterfaceReg***>(CreateInterfaceInternal + s_pInterfaceRegs_Offset);
    #else
        // TODO: CHECK IF THIS DOESN'T BREAK AT SOME POINT
        // convert thunk offset from relative to absolute
        auto s_pInterfaceRegs = *reinterpret_cast<InterfaceReg**>(CreateInterfaceInternal + 9 + *(uintptr_t*)(CreateInterfaceInternal + 11) + *(uintptr_t*)(CreateInterfaceInternal + 28));
    #endif

    void* result = nullptr;
    for ( auto& current = s_pInterfaceRegs; current; current = current->m_pNext ) {
        if ( std::strncmp( current->m_pName, interfaceSymbol, std::strlen(interfaceSymbol) ) == 0 ) {
            result = current->m_CreateFn();
            break;
        }
    }

    if (! result ) {
        console->DevWarning("Portal 2 SDK: Failed to find interface with symbol %s in %s!\n", interfaceSymbol, filename);
        return nullptr;
    }
    return result;
}
