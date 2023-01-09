#pragma once
#include <vector>
#include <memory>

class ParticleManager
{

private:
	// パーティクル配列
	std::vector<std::unique_ptr<class ParticleBase>> m_particles;

public:
	static ParticleManager* GetInstance();
	
	void Initalize();
	void Update();
	void Draw();
	void AddParticle(ParticleBase* particle);

private:
	ParticleManager() = default;
	~ParticleManager() = default;
	ParticleManager(const ParticleManager&) = delete;
	const ParticleManager& operator=(const ParticleManager&) = delete;

	void DeleteParticles();
};

