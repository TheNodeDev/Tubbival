
#include "./TubbivalHUD.hpp"

void TubbivalHUD::Draw() {
	// get width and height for gui drawing
	int width, height;
	engine->GetScreenSize(&width, &height);

	// drawing covering color
	//Color cColor = Color(100, 0, 0);
	//surface->DrawFilledRect(surface->matsurface->ThisPtr(), 100, 100, 120, 120);
}

void EnableTubbUI(const CCommand& args) {
	
}

void DisableTubbUI(const CCommand& args) {

}

Command enableTubbUI("enableTubbUI", EnableTubbUI, "Enable the Tubbival UI");
Command disableTubbUI("disableTubbUI", DisableTubbUI, "Disable the Tubbival UI");

TubbivalHUD* tubbivalHUD = new TubbivalHUD();