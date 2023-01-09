#pragma once
#include "MyMath.h"

class ParticleBase
{

public:
	ParticleBase() {}
	virtual ~ParticleBase() {}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsDelete() = 0;
};

