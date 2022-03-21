#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Particle
{
	Particle() :
		m_Position(0),
		m_Velocity(0),
		m_Color(0),
		m_fRotate(0),
		m_fAge(0),
		m_fLifeTime(0)
	{}

	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	glm::vec4 m_Color;
	float m_fRotate;
	float m_fAge;
	float m_fLifeTime;
	float m_fSize;
};

typedef std::vector<Particle> ParticleBuffer;