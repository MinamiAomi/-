#pragma once
#include "ParticleBase.h"

class NormalParticle :
	public ParticleBase
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	int elapseFrame = 0; // åoâﬂéûä‘
	int activeFrame = 0; // ê∂ë∂Ç∑ÇÈéûä‘ÇÃí∑Ç≥

	float startSize = 1.0f;
	float endSize = 1.0f;

	unsigned int startColor = 0xFFFFFFFF;
	unsigned int endColor = 0x000000FF;

	unsigned int textureHandle;

public:
	NormalParticle() {}
	~NormalParticle() {}

	void Update() override;
	void Draw() override;
	bool IsDelete() override;
};
