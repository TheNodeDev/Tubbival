#include <cstring>
#include "Command.hpp"
#include "module/Tier1.hpp"
#include "PluginBase.hpp"

Command::Command()
    : ptr(nullptr)
    , version(SourceGame_Unknown)
    , isRegistered(false)
    , isReference(false) { }

Command::~Command() {
    if (!isReference) {
        delete ptr;
        ptr = nullptr;
    }
}

Command::Command(const char* name) {
    this->ptr = reinterpret_cast<ConCommand*>(tier1->FindCommandBase(tier1->g_pCVar->ThisPtr(), name));
    this->isReference = true;
}

Command::Command(
		const char* pName,
		_CommandCallback callback,
		const char* pHelpString,
		int flags,
        _CommandCompletionCallback completionFunc
) {
    this->ptr = new ConCommand();
    this->ptr->m_pszName = pName;
    this->ptr->m_pszHelpString = pHelpString;
    this->ptr->m_nFlags = flags;
    this->ptr->m_fnCommandCallback = callback;
    this->ptr->m_fnCompletionCallback = completionFunc;
    this->ptr->m_bHasCompletionCallback = completionFunc != nullptr;
    this->ptr->m_bUsingNewCommandCallback = true;

    Command::GetList().push_back(this);
}

ConCommand* Command::ThisPtr() {
    return this->ptr;
}

auto Command::UniqueFor(int ver) -> void {
    this->version = ver;
}

void Command::Register() {
    if (!this->isRegistered) {
        this->ptr->ConCommandBase_VTable = tier1->ConCommand_VTable;
        tier1->RegisterConCommand(tier1->g_pCVar->ThisPtr(), this->ptr);
        tier1->m_pConCommandList = this->ptr;
    }
    this->isRegistered = true;
}

auto Command::Unregister() -> void {
    if (this->isRegistered) {
        tier1->UnregisterConCommand(tier1->g_pCVar->ThisPtr(), this->ptr);
    }
    this->isRegistered = false;
}

auto Command::operator!() -> bool {
    return this->ptr == nullptr;
}

auto Command::GetList() -> std::vector<Command*>& {
    static std::vector<Command*> list;
    return list;
}

auto Command::RegisterAll(PluginBase* plugin) -> int {
    auto result = 0;
    for (const auto& command : Command::GetList()) {
        if (command->version != SourceGame_Unknown && !(command->version & plugin->game->version)) {
            continue;
        }
        command->Register();
        ++result;
    }
    return result;
}

auto Command::UnregisterAll() -> void {
    for ( const auto& command : Command::GetList() ) {
        command->Unregister();
    }
}

Command* Command::Find(const char* name) {
    for ( const auto& command : Command::GetList() ) {
        if (!std::strcmp(command->ThisPtr()->m_pszName, name)) {
            return command;
        }
    }
    return nullptr;
}

auto Command::Hook(const char* name, _CommandCallback detour, _CommandCallback& original) -> bool {
    auto cc = Command(name);
    if (! !cc ) {
        original = cc.ThisPtr()->m_fnCommandCallback;
        cc.ThisPtr()->m_fnCommandCallback = detour;
        return true;
    }
    return false;
}

auto Command::Unhook(const char* name, _CommandCallback original) -> bool {
    auto cc = Command(name);
    if (!!cc && original) {
        cc.ThisPtr()->m_fnCommandCallback = original;
        return true;
    }
    return false;
}

auto Command::ActivateAutoCompleteFile(const char* name, _CommandCompletionCallback callback) -> bool {
    auto cc = Command(name);
    if (!!cc) {
        cc.ThisPtr()->m_bHasCompletionCallback = true;
        cc.ThisPtr()->m_fnCompletionCallback = callback;
        return true;
    }
    return false;
}

auto Command::DectivateAutoCompleteFile(const char* name) -> bool {
    auto cc = Command(name);
    if (!!cc) {
        cc.ThisPtr()->m_bHasCompletionCallback = false;
        cc.ThisPtr()->m_fnCompletionCallback = nullptr;
        return true;
    }
    return false;
}
