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
	// �폜�Ώۂ̗v�f�ԍ�������
	std::vector<size_t> deleteIndexs;
	// �폜����v�f��T��
	for (size_t i = 0; i < m_particles.size(); i++) {
		if (m_particles[i]->IsDelete() == true) {
			deleteIndexs.emplace_back(i);
		}
	}
	// �폜����v�f������ꍇ
	if (deleteIndexs.empty() == false) {
		if (m_particles.size() == deleteIndexs.size()) {
			// ���ׂč폜����
			m_particles.clear();
		}
		else {
			for (const auto& it : deleteIndexs) {
				// �폜����v�f�ƍŌ���̗v�f�����ւ��Ă���폜
				std::iter_swap(m_particles.begin() + it, m_particles.end() - 1);
				m_particles.pop_back();
			}
		}
	}
}
