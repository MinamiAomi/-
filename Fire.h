#pragma once
#include "MyMath.h"

class Fire
{

private:
	bool m_isActive = false;

	Vector2 m_position;
	float m_radius = 20;

	static unsigned int textureHandle;

public:
	Fire() {}
	~Fire() {}

	static void Initalize();

	void Update();

	void IsActive(bool state) { m_isActive = state; }
	void Position(const Vector2& pos) { m_position = pos; }
	void Radius(float rad) { m_radius = rad; }
};

