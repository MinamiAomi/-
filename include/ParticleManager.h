#pragma once
#include <vector>
#include <list>
#include <memory>

class ParticleManager
{

private:
	// パーティクル配列
	std::list<std::unique_ptr<class ParticleBase>> m_particles;

public:
	static ParticleManager* GetInstance();
	
	void Initalize();
	void Update();
	void Draw();
	void AddParticle(ParticleBase* particle);

	size_t ParticleCount() const { return m_particles.size(); }

private:
	ParticleManager() = default;
	~ParticleManager() = default;
	ParticleManager(const ParticleManager&) = delete;
	const ParticleManager& operator=(const ParticleManager&) = delete;

	void DeleteParticles();
};

