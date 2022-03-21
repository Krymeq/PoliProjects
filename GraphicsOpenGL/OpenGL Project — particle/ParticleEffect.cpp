#include "ParticleEffect.h"
#include "glm/gtx/compatibility.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>


ParticleEffect::ParticleEffect(unsigned int numParticles) :
	m_pCamera(NULL),
	m_pParticleEmitter(NULL),
//	m_ColorInterpolator(glm::vec4(1)),
	m_LocalToWorldMatrix(1),
//	m_TextureID(0),
	m_Force(0, -9.81f, 0)
{
//	Resize(numParticles);
}

ParticleEffect::~ParticleEffect() {}

void ParticleEffect::SetCamera(Camera* pCamera) 
{
	m_pCamera = pCamera;
}
void ParticleEffect::SetParticleEmitter(ParticleEmitter* pEmitter)
{
	m_pParticleEmitter = pEmitter;
}

void ParticleEffect::RandomizeParticle(Particle& particle)
{
	particle.m_fAge = 0.0f;
	particle.m_fLifeTime = (rand() / (float)RAND_MAX) * 5;

	// zmieniæ na losowanie wektora (Random[0..1]*2.0f) - 1.0f
	glm::vec3 unitVec(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand() / (float)RAND_MAX);

	particle.m_Position = unitVec * 1.0f;
	particle.m_Velocity = unitVec * ((rand() % 10) + 10.0f);

}

void ParticleEffect::RandomizeParticles()
{
	for (unsigned int i = 0; i < m_Particles.size(); ++i)
	{
		RandomizeParticle(m_Particles[i]);
	}
}
void ParticleEffect::EmitParticle(Particle& particle)
{
	assert(m_pParticleEmitter != NULL);
	//ustawiæ rozpraszanie jako wskaŸnik na tablicê
	//	m_pParticleEmitter->EmitParticle(particle);
}
void ParticleEffect::EmitParticles()
{
	if (m_pParticleEmitter == NULL)
	{
		RandomizeParticles();
	}
	else
	{
		for (int i = 0; i < m_Particles.size(); i++)
		{
			EmitParticle(m_Particles[i]);
		}
	}
}

void ParticleEffect::Update(float fDeltaTime)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		Particle& particle = m_Particles[i];

		particle.m_fAge += fDeltaTime;
		if (particle.m_fAge > particle.m_fLifeTime)
		{
			if (m_pParticleEmitter != NULL) EmitParticle(particle);
			else RandomizeParticle(particle);
		}

		float lifeRatio = 5;//glm::saturate((particle.m_fAge / particle.m_fLifeTime));
		particle.m_Velocity += (m_Force * fDeltaTime);
		particle.m_Position += (particle.m_Velocity * fDeltaTime);
		particle.m_fRotate += glm::lerp<float>(0.0f, 720.f, lifeRatio);
		particle.m_fSize = glm::lerp<float>(5.0f, 0.0f, lifeRatio);
	}

	BuildVertexBuffer();
}

void ParticleEffect::BuildVertexBuffer()
{
	const glm::vec3 x(0.5, 0, 0);
	const glm::vec3 y(0, 0.5, 0);
	const glm::vec3 z(0, 0, 1.0);

	glm::quat cameraRotation;

	if (m_pCamera != NULL)
	{
		// tutaj w grê wchodzi manipulacja kamer¹, której po³o¿enie ma znaczenie
//		cameraRotation = glm::quat(glm::radians(m_pCamera->GetRotation()));
	}

	m_VertexBuffer.resize(m_Particles.size() * 4, Vertex());

	for (int i = 0; i < m_Particles.size(); i++)
	{
		Particle& particle = m_Particles[i];
		glm::quat rotation = glm::angleAxis(particle.m_fRotate, z);

		int vertexIndex = i * 4;
		Vertex& v0 = m_VertexBuffer[vertexIndex + 0]; // dó³ lewo
		Vertex& v1 = m_VertexBuffer[vertexIndex + 1]; // dó³ prawo
		Vertex& v2 = m_VertexBuffer[vertexIndex + 2]; // góra prawo
		Vertex& v3 = m_VertexBuffer[vertexIndex + 3]; // góra lewo
		// normalnie zasada counterclockwise

		v0.m_Pos = particle.m_Position + (rotation * (-x - y) * particle.m_fSize) * cameraRotation;
		v0.m_Tex0 = glm::vec2(0, 1);
		v0.m_Diffuse = particle.m_Color;

		v1.m_Pos = particle.m_Position + (rotation * (x - y) * particle.m_fSize) * cameraRotation;
		v1.m_Tex0 = glm::vec2(1, 1);
		v1.m_Diffuse = particle.m_Color;

		v2.m_Pos = particle.m_Position + (rotation * (x + y) * particle.m_fSize) * cameraRotation;
		v2.m_Tex0 = glm::vec2(0, 1);
		v2.m_Diffuse = particle.m_Color;

		v3.m_Pos = particle.m_Position + (rotation * (-x + y) * particle.m_fSize) * cameraRotation;
		v3.m_Tex0 = glm::vec2(0, 0);
		v3.m_Diffuse = particle.m_Color;
	}
}
/*
void ParticleEffect::Render()
{
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glDepthMast(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	glPushMartix();
	glMultMatrixf(glm::balue_ptr(m_LocalToWorldMatrix));

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Pos));    
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Tex0));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Diffuse));
	
	// ****************************************
	// tutaj rysowanie, ale to ogarnê jak wrócê
	// mikro-zabawa w main'ie
	// ale chyba do zrobienia
	// do tego z kamer¹ bêdziesz mi musia³ wyt³umaczyæ
	// CALL OFF
	// ****************************************
	glDrawArrays(GL_QUADS, 0, m_VertexBuffer.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopAttrib();

#if _DEBUG
	if (m_pParticleEmitter != NULL)
	{
		m_pParticleEmitter->DebugRender();
	}
#endif

	glPopMatrix();

}*/