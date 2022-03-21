#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "lodepng.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Random.h"

struct Particle {
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec4 Color;
	GLfloat Lifetime;
	glm::mat4 transformMatrix;
	float Angle;

	Particle() :
		Position(0.0f),
		Velocity(0.0f),
		Color(1.0f),
		Lifetime(0.0f),
		transformMatrix(1.0f),
		Angle(0.0f)
	{}
};

class ParticleGenerator {
public:
	ParticleGenerator(ShaderProgram *shader, int amount, glm::vec3 position, float angle, int color = 10);
	~ParticleGenerator();
	void Update(float angle);
	void Draw(glm::mat4 view, glm::mat4 projection, glm::mat4 model = glm::mat4(1.0f));
	GLuint getAmount();

private:
	std::vector<Particle> particles;
	GLuint amount;
	ShaderProgram *shader;
	unsigned int texture;
	glm::vec3 position;

	void loadTexture(std::string filename);
};
