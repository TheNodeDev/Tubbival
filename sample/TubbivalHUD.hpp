#pragma once

#include "engine/Color.hpp"
#include "module/Console.hpp"
#include "module/VScript.hpp"
#include "module/Engine.hpp"
#include "module/VGui.hpp"
#include "module/Surface.hpp"
#include "Command.hpp"
#include "hud/Hud.hpp"

extern Command enableTubbUI;
extern Command disableTubbUI;

class TubbivalHUD : public Hud {
public:
	void Draw();
	bool DrawingOnTop() { return false; }
};

extern TubbivalHUD* tubbivalHUD;
