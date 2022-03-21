#pragma once

#include "Particle.h"
//#include "Interpolator.h"

class Camera;
class ParticleEmitter;

class ParticleEffect
{
public:
	struct Vertex {
		Vertex() :
			m_Pos(0),
			m_Diffuse(0),
			m_Tex0(0)
		{}

		glm::vec3 m_Pos;
		glm::vec4 m_Diffuse;
		glm::vec2 m_Tex0;
	};
	typedef std::vector<Vertex> VertexBuffer;
//	typedef Interpolator<glm::vec4> ColorInterpolator;

	ParticleEffect(unsigned int numParticles = 0);
	~ParticleEffect();

	void SetCamera(Camera* pCamera);
	void SetParticleEmitter(ParticleEmitter* pEmitter);
//	void SetColorInterpolator(const ColorInterpolator& colors);

	void RandomizeParticles();
	void EmitParticles();

	virtual void Update(float fDeltaTime);
//	virtual void Render();

//	bool LoadTexture(const std::string& fileName);

//	void Resize(unsigned int numParticles); // resize buffer

protected:
	void RandomizeParticle(Particle& particle);
	void EmitParticle(Particle& particle);

public:
	void BuildVertexBuffer();
private:
	Camera* m_pCamera;
	ParticleEmitter* m_pParticleEmitter;
//	ColorInterpolator m_ColorInterpolator;

	ParticleBuffer m_Particles;
	VertexBuffer m_VertexBuffer;
	glm::mat4x4 m_LocalToWorldMatrix;
//	GLuint m_TextureID;

	glm::vec3 m_Force;
};

