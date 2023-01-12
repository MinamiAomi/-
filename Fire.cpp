#include "Fire.h"
#include <Novice.h>
#include "Random.h"
#include "ParticleManager.h"
#include "ParticleNormal.h"

unsigned int Fire::textureHandle = 0;

void Fire::Initalize()
{
	textureHandle = Novice::LoadTexture("./images/Particle.png");
}

void Fire::Update()
{
	for (int i = 0; i < 3; i++) {

		if (m_isActive == true) {
			NormalParticle* particle = new NormalParticle;

			float pos_angle = Random() * Math::TwoPi;
			float pos_radius = Random() * m_radius;
			Vector2 direction = Rotated(VECTOR2::UnitX, pos_angle);
			particle->position = m_position + direction * pos_radius;
			particle->velocity = direction * 2.0f;
			particle->acceleration = -VECTOR2::UnitY * 0.1f;
			if (particle->velocity.y > 0) {
				particle->acceleration.y += Dot(-VECTOR2::UnitY, particle->velocity) * 0.1f;
			}


			particle->activeFrame = (int)Math::Lerp(Random(), 30, 40);
			particle->elapseFrame = 0;

			if (particle->velocity.x != 0) {
				particle->acceleration.x = -particle->velocity.x / (float)particle->activeFrame * 1.4f;
			}


			particle->startSize = Math::Lerp(Random(), 30.0f, 40.0f);
			particle->endSize = 20;

		

			//unsigned int color = Color::HsvaToRgba(Math::Lerp(Random(), 0.0f, 360.0f), 1.0f, 1.0f, 0xFF);

			particle->startColor = 0xFF7350FF;
			particle->endColor = 0xFFA53000;

			particle->textureHandle = textureHandle;

			//fire->startColor = color;
			//fire->endColor = color;

			ParticleManager::GetInstance()->AddParticle(particle);
		}

	}
}
