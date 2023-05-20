#include "Features/Hud/Hud.hpp"
#include "Modules/Scheme.hpp"
#include "Modules/Surface.hpp"
#include "Modules/Engine.hpp"
#include "Variable.hpp"

Variable tubbival_hub("tubbival_hud", "0", 0, "Draws tubbival HUD.\n");

class TubbivalHUD : public Hud {
public:
	TubbivalHUD()
		: Hud(HudType_InGame | HudType_Paused | HudType_Menu | HudType_LoadingScreen, false) {
	}

	bool ShouldDraw() override {
		return tubbival_hub.GetBool();
	}

	bool GetCurrentSize(int &w, int &h) override {
		return false;
	}

	void Paint(int slot) override {
		int screenWidth, screenHeight;
		engine->GetScreenSize(nullptr, screenWidth, screenHeight);

		Surface::HFont font = 6;

		int width = surface->GetFontLength(font, "%s", "UwuTubbival");

		surface->DrawTxt(font, (screenWidth - width) / 2, screenHeight - 10, Color{255, 255, 255, 100}, "%s", "Hello");
	}
};

TubbivalHUD tubbivalhud;