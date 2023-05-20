#pragma once

#include "Variable.hpp"

class Cheats {
public:
    void Init( PluginBase* plugin );
    void Shutdown();
};

extern Variable sv_transition_fade_time;
extern Variable ui_loadingscreen_transition_time;
extern Variable ui_loadingscreen_fadein_time;
extern Variable ui_loadingscreen_mintransition_time;

extern Variable sv_cheats;
extern Variable crosshair;
extern Variable viewmodel_offset_z;
extern Variable puzzlemaker_play_sounds;