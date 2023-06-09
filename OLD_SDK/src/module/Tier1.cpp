#include "module/Tier1.hpp"
#include "Offsets.hpp"

Tier1::Tier1() : Module() { }

auto Tier1::Init( PluginBase* plugin ) -> bool {
    this->g_pCVar = Interface::Create(this->Name(), "VEngineCvar0", false);
    if ( this->g_pCVar ) {
        this->RegisterConCommand = this->g_pCVar->Original<_RegisterConCommand>(Offsets::RegisterConCommand);
        this->UnregisterConCommand = this->g_pCVar->Original<_UnregisterConCommand>(Offsets::UnregisterConCommand);
        this->FindCommandBase = this->g_pCVar->Original<_FindCommandBase>(Offsets::FindCommandBase);

        this->m_pConCommandList = (ConCommandBase*)((uintptr_t)this->g_pCVar->ThisPtr() + Offsets::m_pConCommandList);

        auto listdemo = reinterpret_cast<ConCommand*>(this->FindCommandBase(this->g_pCVar->ThisPtr(), "listdemo"));
        if (listdemo) {
            this->ConCommand_VTable = listdemo->ConCommandBase_VTable;

            if (listdemo->m_fnCompletionCallback) {
                auto callback = (uintptr_t)listdemo->m_fnCompletionCallback + Offsets::AutoCompletionFunc;
                this->AutoCompletionFunc = Memory::Read<_AutoCompletionFunc>(callback);
            }
        }

        auto sv_lan = reinterpret_cast<ConVar*>(this->FindCommandBase(this->g_pCVar->ThisPtr(), "sv_lan"));
        if (sv_lan) {
            this->ConVar_VTable = sv_lan->ConCommandBase_VTable;
            this->ConVar_VTable2 = sv_lan->ConVar_VTable;
        }
    }

    return this->hasLoaded = this->g_pCVar
        && this->ConCommand_VTable
        && this->ConVar_VTable
        && this->ConVar_VTable2
        && this->AutoCompletionFunc;
}

auto Tier1::Shutdown() -> void {
    Interface::Delete(this->g_pCVar);
}

Tier1* tier1;
