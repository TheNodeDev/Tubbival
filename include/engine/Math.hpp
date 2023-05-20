//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include <cmath>

struct Vector {
	float x, y, z;
	Vector() : x(0), y(0), z(0) {};
	Vector(float x, float y, float z) { this->x = x; this->y = y;  this->z = z; };
	inline float Length() {
		return std::sqrt(x * x + y * y + z * z);
	}

	inline float Length2D() {
		return std::sqrt(x * x + y * y);
	}

	inline Vector operator*(float fl) {
		Vector res;
		res.x = x * fl;
		res.y = y * fl;
		res.z = z * fl;
		return res;
	}

	inline Vector operator+(Vector vec) {
		Vector res;
		res.x = x + vec.x;
		res.y = y + vec.y;
		res.z = z + vec.z;
		return res;
	}

	inline float& operator[](int i) {
		return ( (float*) this )[i];
	}

	inline float operator[](int i) const {
		return ( (float*) this )[i];
	}

	inline float operator*(Vector vec) {
		return x * vec.x + y * vec.y + z * vec.z;
	}

	inline Vector operator^(Vector vec) {
		Vector res;
		res.x = y * vec.z - z * vec.y;
		res.y = z * vec.x - x * vec.z;
		res.z = x * vec.y - y * vec.x;
		return res;
	}
};

#ifndef __GNUC__
	struct __declspec(align(16)) VectorAligned : public Vector {
#else
	struct VectorAligned : public Vector {
#endif
	VectorAligned() : Vector(), w(0) {};
	VectorAligned(float x, float y, float z) : Vector(x, y, z) , w(0) {}
	float w;
};

struct matrix3x4_t {
	float m_flMatVal[3][4];
};

struct VMatrix {
	float m[4][4];
};

struct QAngle {
	float x, y, z;
};

typedef union {
	float  m128_f32[4];
	unsigned int m128_u32[4];
} fltx4;