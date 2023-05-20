#include "module/VScript.hpp"
#include "Offsets.hpp"
#include "PluginBase.hpp"


REDECL(VScript::CreateVM);
#ifdef _WIN32
    DETOUR_STD(IScriptVM*, VScript::CreateVM, ScriptLanguage_t language)
#else
    DETOUR_T(IScriptVM*, VScript::CreateVM, ScriptLanguage_t language)
#endif
{
    auto g_pScriptVM = VScript::CreateVM(
        #ifndef _WIN32
            thisptr,
        #endif
        language
    );

	vscript->g_pScriptVM = g_pScriptVM;
	vscript->plugin->OnRegisterScripts();

    return g_pScriptVM;
}

VScript::VScript() : Module() { }

auto VScript::Init( PluginBase* plugin ) -> bool {
    this->scriptmanager = Interface::Create(MODULE("vscript"), "VScriptManager0");
    if ( this->scriptmanager ) {
        this->scriptmanager->Hook(VScript::CreateVM_Hook, VScript::CreateVM, Offsets::CreateVM);
    }
	this->plugin = plugin;

    return this->hasLoaded = this->scriptmanager;
}

auto VScript::Shutdown() -> void {
    Interface::Delete(this->scriptmanager);
}

VScript* vscript;
