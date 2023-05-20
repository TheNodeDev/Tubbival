//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

struct Color {
	Color(){
		*( (int*) this ) = 255;
	}

	Color(int _r, int _g, int _b) {
		SetColor(_r, _g, _b, 255);
	}

	Color(int _r, int _g, int _b, int _a) {
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255) {
		_color[0] = (unsigned char) _r;
		_color[1] = (unsigned char) _g;
		_color[2] = (unsigned char) _b;
		_color[3] = (unsigned char) _a;
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }
	unsigned char _color[4];
};

enum TextColor {
	COLOR_NORMAL = 1, // 255, 178.5, 0.0, 255
	COLOR_USEOLDCOLORS = 2, // 255, 178.5, 0.0, 255
	COLOR_PLAYERNAME = 3, // 204, 204, 204, 255
	COLOR_LOCATION = 4, // 153, 255, 153, 255
	COLOR_ACHIEVEMENT = 5, // 64, 255, 64, 255
	COLOR_MAX
};