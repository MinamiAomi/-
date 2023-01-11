#include "ParticleNormal.h"
#include "ParticleManager.h"
#include <Novice.h>
#include "Random.h"

void NormalParticle::Update()
{
	elapseFrame++;
	velocity += acceleration;
	position += velocity;
}

void NormalParticle::Draw()
{
	float t = (float)elapseFrame / (float)activeFrame;

	float size = Math::Lerp(t, startSize, endSize);

	unsigned int color = Color::Lerp(t, startColor, endColor);

	float hsize = size * 0.5f;

	Vector2 leftTop = {
		position.x - hsize,
		position.y - hsize };
	Novice::SetBlendMode(kBlendModeAdd);
	auto s = size / 256.0f;
	Novice::DrawSpriteRect((int)leftTop.x, (int)leftTop.y, 0, 0, 256, 256, textureHandle, s, s, 0.0f, color);
	Novice::SetBlendMode(kBlendModeNormal);
}

bool NormalParticle::IsDelete()
{
	return elapseFrame >= activeFrame;
}