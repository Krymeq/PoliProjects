#pragma once;

#include "Particle.h"

class SphereEmitter
{
public:
	SphereEmitter();
	void EmitParticle(Particle& particle);
	void DebugRender();

	float MinRadius;
	float MaxRadius;

	float MinInclination;
	float MaxInclination;

	float MinAzimuth;
	float MaxAzimuth;

	float MinSpeed;
	float MaxSpeed;

	float MinLifetime;
	float MaxLifetime;

	glm::vec3 Origin;

private:
	void RenderSphere(glm::vec4 color, float fRadius);
};
