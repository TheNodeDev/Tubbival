#pragma once

#include "engine/Color.hpp"

/**
 * Abstract class representing a bare-bones HUD element
 *
 * An object of a subclass of this class is considered an in-game HUD.
 */
class Hud {
public:
    /**
     *
     * @return if this element should be drawn on top (of what?)
     */
	virtual bool DrawingOnTop() { return false; }

    /**
     * Draws this element
     */
	virtual void Draw();
};
