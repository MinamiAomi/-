#include "Player.h"
#include <Novice.h>
#include "ParticleNormal.h"
#include "ParticleManager.h"

void Player::Initalize()
{
	m_textureHandle = Novice::LoadTexture("./images/Particle.png");
}

void Player::Update(char* key, char* preKey)
{
	m_velocity.x = 0;
	if (key[DIK_D] != 0) {
		m_velocity.x += 3;
	}
	if (key[DIK_A] != 0) {
		m_velocity.x += -3;
	}

	if (key[DIK_W] != 0 && m_isJump == false) {
		m_velocity.y += -m_jumpSpeed;
		m_isJump = true;
		m_isGround = false;
	}

	m_velocity.y += m_gravity;
	m_position += m_velocity;


	if (m_position.y >= 600 - m_size.y * 0.5f) {
		m_position.y = 600 - m_size.y * 0.5f;
		m_velocity.y = 0;
		m_isJump = false;
		if (m_isGround == false) {
			CreateLandingEffect();
		}
	}
}

void Player::Draw()
{

	Vector2 lefttop = m_position - m_size * 0.5f;
	Novice::DrawBox((int)lefttop.x, (int)lefttop.y, m_size.x, m_size.y, 0.0f, WHITE,kFillModeSolid);
}

void Player::CreateLandingEffect()
{
	static const int halfCount = kLandingEffectCount / 2.0f;
	
	static const Vector2 kEmitterOffset = { m_size.x * 0.5f, m_size.y * 0.5f };

	for (int i = 0; i < kLandingEffectCount; i++) {
		int j = i % halfCount;
		int side = i < halfCount ? -1 : 1;

		NormalParticle* particle = new NormalParticle;
		
		particle->position = m_position + Vector2(kEmitterOffset.x * side, kEmitterOffset.y);
		particle->velocity = Vector2(j * 1.0f * side / 3.0f, 0);
		particle->acceleration = Vector2(0.1f * side, -0.17f);

		particle->activeFrame = 20;
		
		particle->startSize = Math::Map(j, 0, halfCount, 10, 20);
		particle->endSize = Math::Map(j, 0, halfCount, 30, 40);

		particle->startColor = 0xAAAAAAFF;
		particle->endColor = 0x55555500;
		particle->textureHandle = m_textureHandle;



		ParticleManager::GetInstance()->AddParticle(particle);
	}
	m_isGround = true;
}