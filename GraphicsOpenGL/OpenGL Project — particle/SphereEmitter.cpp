#include "SphereEmitter.h"

SphereEmitter::SphereEmitter() :
	MinRadius(0),
	MaxRadius(1),
	MinInclination(0),
	MaxInclination(180),
	MinAzimuth(0),
	MaxAzimuth(360),
	MinSpeed(10),
	MaxSpeed(20),
	MinLifetime(3),
	MaxLifetime(5),
	Origin(0)
{}
/*
void SphereEmitter::EmitParticle(Particle& particle)
{
	float inclination; // = glm::radians(RandRange(Min,Max));
	float azimuth; // = glm::radians(RandRange(Min,Max));

	// Nie mia³em si³y siê bawiæ w zmianê funkcji, wiêc napisa³em obrazowo Random(from No. ,  to No.)
	float radius = RandRange(Min, Max);
	float speed = RandRange(Min, Max);
	float lifetime = RandRange(Min, Max);

	float sInclination = sinf(inclination);

	float x = sInclination * cosf(azimuth);
	float y = sInclination * sinf(azimuth);
	float z = cosf(inclination);

	glm::vec3 vector(x, y, z);

	particle.m_Position = (vector * radius) + Origin;
	particle.m_Velocity = vector * speed;

	particle.m_fLifeTime = lifetime;
	particle.m_fAge = 0;
}

// Tego ni¿ej jeszcze nie ogarn¹³em


void SphereEmitter::RenderSphere(glm::vec4 color, float fRadius)
{
	float X, Y, Z, inc, azi;

	glColor4fv(glm::value_ptr(color));

	glPointSize(2.0f);
	glBegin(GL_POINTS);

	for (float azimuth = MinAzimuth; azimuth < MaxAzimuth; azimuth += 5.0f)
	{
		for (float inclination = MinInclination; inclination < MaxInclination; inclination += 5.0f)
		{
			inc = glm::radians(inclination);
			azi = glm::radians(azimuth);

			X = fRadius * sinf(inc) * cosf(azi);
			Y = fRadius * sinf(inc) * sinf(azi);
			Z = fRadius * cosf(inc);

			glVertex3f(X, Y, Z);
		}

		inc = glm::radians(MaxInclination);
		azi = glm::radians(azimuth);

		X = fRadius * sinf(inc) * cosf(azi);
		Y = fRadius * sinf(inc) * sinf(azi);
		Z = fRadius * cosf(inc);

		glVertex3f(X, Y, Z);
	}

	inc = glm::radians(MaxInclination);
	azi = glm::radians(MaxAzimuth);

	X = MaximumRadius * sinf(inc) * cosf(azi);
	Y = MaximumRadius * sinf(inc) * sinf(azi);
	Z = MaximumRadius * cosf(inc);

	glVertex3f(X, Y, Z);

	glEnd();
}

void SphereEmitter::DebugRender()
{
	glTranslatef(Origin.x, Origin.y, Origin.z);

	//    RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
	RenderSphere(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius);

	glTranslatef(-Origin.x, -Origin.y, -Origin.z);
}
*/