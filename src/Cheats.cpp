#include "Command.hpp"
#include "Variable.hpp"
#include "Cheats.hpp"

Variable sv_transition_fade_time;
Variable ui_loadingscreen_transition_time;
Variable ui_loadingscreen_fadein_time;
Variable ui_loadingscreen_mintransition_time;

Variable sv_cheats;
Variable crosshair;
Variable viewmodel_offset_z;
Variable puzzlemaker_play_sounds;

auto Cheats::Init( PluginBase* plugin ) -> void {
    sv_transition_fade_time = Variable("sv_transition_fade_time");
    ui_loadingscreen_transition_time = Variable("ui_loadingscreen_transition_time");
    ui_loadingscreen_fadein_time = Variable("ui_loadingscreen_fadein_time");
    ui_loadingscreen_mintransition_time = Variable("ui_loadingscreen_mintransition_time");

    sv_transition_fade_time.Modify(FCVAR_DEVELOPMENTONLY, FCVAR_CHEAT | FCVAR_HIDDEN);
    sv_transition_fade_time.SetValue(0);
    sv_transition_fade_time.ThisPtr()->m_pszDefaultValue = "0";
    ui_loadingscreen_transition_time.Modify(FCVAR_DEVELOPMENTONLY, FCVAR_CHEAT | FCVAR_HIDDEN);
    ui_loadingscreen_transition_time.SetValue(0);
    ui_loadingscreen_transition_time.ThisPtr()->m_pszDefaultValue = "0";
    ui_loadingscreen_fadein_time.Modify(FCVAR_DEVELOPMENTONLY, FCVAR_CHEAT | FCVAR_HIDDEN);
    ui_loadingscreen_fadein_time.SetValue(0);
    ui_loadingscreen_fadein_time.ThisPtr()->m_pszDefaultValue = "0";
    ui_loadingscreen_mintransition_time.Modify(FCVAR_DEVELOPMENTONLY, FCVAR_CHEAT | FCVAR_HIDDEN);
    ui_loadingscreen_mintransition_time.SetValue(0);
    ui_loadingscreen_mintransition_time.ThisPtr()->m_pszDefaultValue = "0";

    sv_cheats = Variable("sv_cheats");
    crosshair = Variable("crosshair");
    viewmodel_offset_z = Variable("viewmodel_offset_z");
    puzzlemaker_play_sounds = Variable("puzzlemaker_play_sounds");


    Variable::RegisterAll( plugin );
    Command::RegisterAll( plugin );
}

auto Cheats::Shutdown() -> void {
    Variable::UnregisterAll();
    Command::UnregisterAll();
}
