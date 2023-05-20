#pragma once
#include <vector>

#include "Module.hpp"

#include "../Interface.hpp"
#include "../Utils.hpp"
#include "Surface.hpp"
#include "hud/Hud.hpp"

/**
 * Represents the vgui2 DLL
 */
class VGui : public Module {
public:
    Interface* enginevgui = nullptr;
    Interface* g_pScheme = nullptr;

    using _GetFont = unsigned long(__funccc*)(void* thisptr, const char* fontName, bool proportional);
    _GetFont GetFont = nullptr;
    unsigned long GetDefaultFont();
    void AllowCustomHudThisFrame() {
		canDrawThisFrame = true;
	}
	/**
	 * Internal
	 */
    void DrawCustomHud(Hud* hud);
	/**
	 * Adds an hud to the drawable list
	 */
	 void AddCustomHud(Hud* hud) {
		 huds.push_back( hud );
	}
private:
    bool canDrawThisFrame = true;
    std::vector<Hud*> huds;
public:
    // CEngineVGui::Paint
    DECL_DETOUR(Paint, int mode);

    bool Init( PluginBase* plugin ) override;
    void Shutdown() override;
    const char* Name() override { return MODULE("engine"); }
};

extern VGui* vgui;
