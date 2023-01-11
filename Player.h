#pragma once
#include "MyMath.h"
#include "ParticleBase.h"

class Player
{

private:
	static const int kLandingEffectCount = 20;

	Vector2 m_position;
	Vector2 m_velocity;

	float m_jumpSpeed = 20;
	float m_gravity = 0.6f;
	
	bool m_isJump = false;
	bool m_isGround = false;
	Vector2 m_size = { 50,100 };

	unsigned int m_textureHandle;


public:
	Player() {}
	~Player() {}

	void Initalize();
	void Update(char* key, char* preKey);
	void Draw();

private:
	void CreateLandingEffect();

};

