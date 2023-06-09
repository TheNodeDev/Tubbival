#pragma once
#include "Module.hpp"

#include "Utils.hpp"
#include "Interface.hpp"
#include "engine/CVar.hpp"

#ifdef _WIN32
#define TIER1 "vstdlib"
#else
#define TIER1 "libvstdlib"
#endif

/**
 * Represents the vstdlib DLL
 */
class Tier1 : public Module {
public:
    Interface* g_pCVar = nullptr;
    ConCommandBase* m_pConCommandList = nullptr;

    /**
     * Registers a console command
     * @param pCommandBase
     */
    _RegisterConCommand RegisterConCommand = nullptr;
	/**
	 * Unregisters a console command
	 * @param pCommandBase
	 */
    _UnregisterConCommand UnregisterConCommand = nullptr;
	/**
	 * Finds a console command by name
	 * @param name
	 * @return CommandBase* or null (?)
	 */
    _FindCommandBase FindCommandBase = nullptr;

    void* ConCommand_VTable = nullptr;
    void* ConVar_VTable = nullptr;
    void* ConVar_VTable2 = nullptr;
    /**
     * Finds candidates for a partial command
     * @param partial partial name of the command
     * @return char matrix of [COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH]
     */
    _AutoCompletionFunc AutoCompletionFunc = nullptr;

    Tier1();
    bool Init( PluginBase* plugin ) override;
    void Shutdown() override;
    const char* Name() override { return MODULE(TIER1); }
};

extern Tier1* tier1;
