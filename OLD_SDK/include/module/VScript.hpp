#pragma once
#include "engine/vscript/ScriptVM.hpp"
#include "Interface.hpp"
#include "Utils.hpp"
#include "Module.hpp"

/**
 * Represents the vscript DLL
 */
class VScript : public Module {
public:
    Interface* scriptmanager = nullptr;
	PluginBase* plugin = nullptr;

    IScriptVM* g_pScriptVM;
public:
    VScript();
    bool Init( PluginBase* plugin ) override;
    void Shutdown() override;
	/**
	 * Get the module name
	 * */
    const char* Name() override { return MODULE("vscript"); }

    // CScriptManager::CreateVM
    #ifdef _WIN32
        DECL_DETOUR_STD(IScriptVM*, CreateVM, ScriptLanguage_t language);
    #else
        DECL_DETOUR_T(IScriptVM*, CreateVM, ScriptLanguage_t language);
    #endif
};

extern VScript* vscript;
