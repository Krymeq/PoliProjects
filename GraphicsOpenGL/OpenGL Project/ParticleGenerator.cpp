#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(ShaderProgram *shader, int amount, glm::vec3 position, float angle, int color) :
	shader(shader),
	amount(amount),
	position(position)
{
	this->loadTexture("particle.png");

	for (int i = 0; i < this->amount; i++)
	{
		this->particles.push_back(Particle());
	}

	// new particles
	for (int i = 0; i < this->amount; i++)
	{
		
		switch (color)
		{
		case 0: // ground (brown - darkgreen)
			this->particles[i].Color = glm::vec4(102 / 255.0f, RandRange(30, 140) / 255.0f, 0.0f, 1.0f);
			this->particles[i].Velocity = 0.5f * RandUnitVec();
			this->particles[i].Lifetime = RandRange(1.2f, 1.5f);
			break;
		case 1: // fire (yellow - red)
			this->particles[i].Color = glm::vec4(255 / 255.0f, RandRange(69, 255) / 255.0f, 0.0f, 1.0f);
			this->particles[i].Velocity = 0.3f * RandUnitVec();
			this->particles[i].Lifetime = RandRange(0.3f, 0.5f);
			break;
		default:
			float rColor = 0.5 + ((rand() % 100) / 100.0f);
			this->particles[i].Color = glm::vec4(rColor, rColor, rColor, 1.0f);
			this->particles[i].Velocity = 1.0f * RandUnitVec();
			this->particles[i].Lifetime = RandRange(1.2f, 1.6f);
			break;
		}

		this->particles[i].Position = position;
		this->particles[i].transformMatrix = glm::rotate(this->particles[i].transformMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

ParticleGenerator::~ParticleGenerator()
{

}

GLuint ParticleGenerator::getAmount()
{
	return this->amount;
}

void ParticleGenerator::Update(float angle)
{
	int particleNumber = amount;
	for (int i = 0; i < particleNumber; i++)
	{
		Particle &par = particles[i];
		par.Lifetime -= 0.1f;
		if (par.Lifetime > 0.0f)
		{
			par.transformMatrix = glm::translate(par.transformMatrix, glm::vec3(0.0,0.0, par.Velocity.z));
			par.Position += par.Velocity;
			par.Color.a -= 2.5;
		}
		else if (par.Lifetime <= 0.0f)
		{
			this->amount -= 1;
		}
	}
}

void ParticleGenerator::Draw(glm::mat4 view, glm::mat4 projection, glm::mat4 model)
{
	float particle_quad[]{
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader->use();
	for (Particle particle : this->particles)
	{
		if (particle.Lifetime > 0.0f)
		{
			glBindTexture(GL_TEXTURE_2D, this->texture);
			glm::mat4 m = model * particle.transformMatrix;

			glUniformMatrix4fv((this->shader)->u("model"), 1, false, glm::value_ptr(model));
			glUniformMatrix4fv((this->shader)->u("view"), 1, false, glm::value_ptr(view));
			glUniformMatrix4fv((this->shader)->u("projection"), 1, false, glm::value_ptr(projection));
			glUniform3fv((this->shader)->u("offset"), 1, glm::value_ptr(particle.Position));
			glUniform4fv((this->shader)->u("color"), 1, glm::value_ptr(particle.Color));

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, particle_quad);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::loadTexture(std::string path)
{
	std::vector<unsigned char> texData;

	unsigned int width, height;
	unsigned int error = lodepng::decode(texData, width, height, path);

	glGenTextures(1, &(this->texture));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data());

	glGenerateMipmap(GL_TEXTURE_2D);
}
