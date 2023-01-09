#include "ParticleManager.h"
#include "ParticleBase.h"

ParticleManager* ParticleManager::GetInstance() {
	static ParticleManager instance;
	return &instance;
}

void ParticleManager::Update()
{
	DeleteParticles();

	for (auto& it : m_particles) {
		it->Update();
	}
}

void ParticleManager::Draw()
{
	for (auto& it : m_particles) {
		it->Draw();
	}
}

void ParticleManager::AddParticle(ParticleBase* particle)
{
	m_particles.emplace_back(particle);
}

void ParticleManager::DeleteParticles()
{
	// íœ‘ÎÛ‚Ì—v‘f”Ô†‚ª“ü‚é
	std::vector<size_t> deleteIndexs;
	// íœ‚·‚é—v‘f‚ğ’T‚·
	for (size_t i = 0; i < m_particles.size(); i++) {
		if (m_particles[i]->IsDelete() == true) {
			deleteIndexs.emplace_back(i);
		}
	}
	// íœ‚·‚é—v‘f‚ª‚ ‚éê‡
	if (deleteIndexs.empty() == false) {
		if (m_particles.size() == deleteIndexs.size()) {
			// ‚·‚×‚Äíœ‚·‚é
			m_particles.clear();
		}
		else {
			for (const auto& it : deleteIndexs) {
				// íœ‚·‚é—v‘f‚ÆÅŒã”ö‚Ì—v‘f‚ğ“ü‚ê‘Ö‚¦‚Ä‚©‚çíœ
				std::iter_swap(m_particles.begin() + it, m_particles.end() - 1);
				m_particles.pop_back();
			}
		}
	}
}
