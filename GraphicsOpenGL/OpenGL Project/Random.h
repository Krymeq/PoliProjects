#pragma once;
#include <iostream>
#include <glm/glm.hpp>

// Generate a random number between [0..1)
inline float Random()
{
	return rand() / (float)RAND_MAX;
}

inline float RandRange(float fMin, float fMax)
{
	if (fMin > fMax) std::swap(fMin, fMax);
	return (Random() * (fMax - fMin)) + fMin;
}

inline glm::vec3 RandUnitVec()
{
	float x = ((Random() * 2.0f) - 1.0f) * 0.1;
	float y = ((Random() * 2.0f) - 1.0f) * 0.1;
	float z = ((Random() * 2.0f) - 1.0f) * 0.1;

	return glm::normalize(glm::vec3(x, y, z));
}
