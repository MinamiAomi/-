#pragma once
#include "MyMath.h"


class Coin
{
public:
	enum State {
		kInactive,
		kActive,
		kCaught
	};

private:
	static const Vector2 kSize;
	static const Vector2 kHalfSize;
	static int textureHandle;

public:
	State state = kInactive;
	Vector2 position;
	
public:
	Coin() {}
	~Coin() {}

	static void Initalize();
	void Update();
	void Draw();
};

