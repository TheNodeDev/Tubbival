//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "engine/Color.hpp"
#include "hud/Hud.hpp"

class StaminaHud : public Hud {
private:
	int staminaTexture = 0;
	Color staminaColor;
public:
	void Draw();
	int GetStaminaTexture();
	void SetStaminaColor(Color c) { staminaColor = c; };
};

extern StaminaHud* staminaHud;



class CelesteBerryHud : public Hud {
private:
	int berryTexture[8];
	int indicatorTexture = 0;

	int displayBerryCount = 0;
	int oldBerryCount = 0;
	float posOffset = 0.0;
	float posOffset2 = 0.0; // ah, yes, good variable name // ENDER approves
	float collectAnimState = 0.0;
	float prevRealTime = 0;
public:
	void Draw();
	bool DrawingOnTop() { return true; }
	int GetBerryTexture(int type);
};

extern CelesteBerryHud* celesteBerryHud;