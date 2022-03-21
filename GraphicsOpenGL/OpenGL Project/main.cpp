#define GLM_FORCE_RADIANS
#include <Windows.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <GLFW/glfw3.h>
#include <chrono>
#include <math.h>
#include <iostream>
#include <list>
#include <vector>
#include "Czolg.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "ParticleGenerator.h"

struct Missile
{
	Model *bullet;
	float verticalSpeed;
};


Czolg *cz;

Model *bulletTemplate;
Model *terrain = new Model();
ShaderProgram *spLambert;
ShaderProgram *spTerrain;
ShaderProgram *spParticle;

glm::mat4 translate = glm::mat4(1.0f);
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, -15.0f);
glm::vec3 cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFrontAxis = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 lightPosition = glm::vec3(25.0, 25.0, -75.0);
glm::vec3 lightColor = glm::vec3(1.0f, 0.85f, 0.75f);

std::list<Missile*> missiles;
std::list<ParticleGenerator*> particles;
ParticleGenerator* test;


short int accFactor;
float cameraRotation = 0.0f;
int speed;
int rotateFactor;
int cannonRotation;
int screenWidth;
int screenHeight;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			accFactor = 1;
		if (key == GLFW_KEY_S)
			accFactor = -1;
		if (key == GLFW_KEY_A)
			rotateFactor = 1;
		if (key == GLFW_KEY_D)
			rotateFactor = -1;
		if (key == GLFW_KEY_Q)
			cannonRotation = 1;
		if (key == GLFW_KEY_E)
			cannonRotation = -1;
		if (key == GLFW_KEY_SPACE)
		{
			Missile *miss = new Missile();
			Model *m = new Model(bulletTemplate);

			float a = glm::radians(cz->getAngle());
			
			//Offset between the middle of the tank and the tip of the cannon
			glm::vec3 offset = glm::vec3(6.5f * sin(a) + 0.1f * cos(a), 2.22f, 6.5f * cos(a) - 0.1f * sin(a));
			
			//Translating bullet so that it would be "shot" from the cannon
			//Also - spawning (put BOOM here)
			m->translate(cz->getTurretPosition() + offset);
			m->scale(glm::vec3(0.03f, 0.03f, 0.03f));
			m->rotate(a * 180.0f / 3.1415f , glm::vec3(0.0f, 1.0f, 0.0f));
			m->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			
			miss->bullet = m;
			miss->verticalSpeed = 0.0f;

			missiles.push_back(miss);

			particles.push_back(new ParticleGenerator(spParticle, 200, cz->getTurretPosition() + offset, 1));
		}

		if (key == GLFW_KEY_R)
		{
			cz->setTransformMatrix(glm::mat4(1.0f));
			cameraRotation = 0.0f;
			cameraPosition = glm::vec3(0.0f, 5.0f, -15.0f);
			cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
			cameraFrontAxis = glm::vec3(0.0f, -0.3f, 1.0f);
		}
	}

	if (action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
			cameraRotation += 2.5f;
		if (key == GLFW_KEY_LEFT)
			cameraRotation -= 2.5f;
	}

	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)
			accFactor = 0;
		if (key == GLFW_KEY_A || key == GLFW_KEY_D)
			rotateFactor = 0;
		if (key == GLFW_KEY_Q || key == GLFW_KEY_E)
			cannonRotation = 0;
	}
}

void callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screenHeight = height;
	screenWidth = width;
}

void initialize(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, callback);
	glfwSetKeyCallback(window, keyCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Can't initialize GLEW\n";
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_DEPTH_TEST);
}

void renderLoop(GLFWwindow* window)
{
	GLfloat color[] = { 0.6f, 0.9f, 1.0f, 1.0f };
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)(screenWidth / screenHeight), 1.0f, 100.0f);


	while (!glfwWindowShouldClose(window))
	{
		auto start = std::chrono::steady_clock::now();


		glm::vec3 tankPos = cz->getTurretPosition();
		float a = cz->getAngle();

		//setting camera behind the cannon
		cameraPosition = glm::vec3(tankPos.x - 15 * sin(glm::radians(a + cameraRotation)), 5, tankPos.z - 15 * cos(glm::radians(a + cameraRotation)));
		viewMatrix = glm::lookAt(cameraPosition, tankPos, cameraUpAxis);

		glClearColor(0.6f, 0.9f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform3fv(spLambert->u("lightColor"), 1, glm::value_ptr(lightColor));
		
		//calculating current speed
		if (accFactor != 0)
		{
			if (abs(speed) < 1600)
				speed += accFactor * 40;
		}
		else if (speed != 0)
		{
			speed -= 10 * ((speed > 0) ? 1 : ((speed < 0) ? -1 : 0));
			if (speed < 60 && speed > -60)
				speed = 0;
		}
		
		cz->translate(glm::vec3(0.0, 0.0, 0.1) * ((float)speed / 1000));
		cz->rotate(1.0f * rotateFactor, glm::vec3(0.0, 1.0, 0.0));
		cz->rotateTurret(1.0f * cannonRotation);

		//Loop used to handle bullets
		for (std::list<Missile*>::iterator it = missiles.begin(); it != missiles.end();)
		{
			Missile *missile = (*it);
			missile->bullet->draw(spLambert, viewMatrix, projectionMatrix);
			
			glm::vec3 speedVector = glm::vec3(0.0f, 100.0f, missile->verticalSpeed);

			missile->verticalSpeed += (9.81f / 25.0f);
			missile->bullet->translate(speedVector);
			
			//Despawn (put BOOM here)
			if (missile->bullet->getTransformMatrix()[3][1] <= 0.0f)
			{
				glm::vec3 position = glm::vec3(missile->bullet->getTransformMatrix()[3][0], missile->bullet->getTransformMatrix()[3][1], missile->bullet->getTransformMatrix()[3][2]);
				particles.push_back(new ParticleGenerator(spParticle, 700, position, cz->getAngle(), 0));
				
				it = missiles.erase(it);
				delete(missile->bullet);
				delete(missile);

				printf("cz->angle = %f\n", cz->getAngle());
				printf("Despawned an element. List size: %d\n", missiles.size());

			}
			else it++;
		}

		for (std::list<ParticleGenerator*>::iterator it = particles.begin(); it != particles.end();)
		{
			ParticleGenerator *particle = (*it);
			particle->Draw(viewMatrix, projectionMatrix);
			particle->Update(cz->getAngle());
			if (particle->getAmount() == 0) {
				it = particles.erase(it);
				particle->~ParticleGenerator();
				printf("Deleted an particle generator.\n");
			}
			else it++;
		}

		cz->draw(spLambert, viewMatrix, projectionMatrix);
		terrain->draw(spLambert, viewMatrix, projectionMatrix);


		auto stop = std::chrono::steady_clock::now();
		float duration = 1000.0f/60.0f - (float)std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

		//calculating delay for 60FPS
		Sleep((duration > 0) ? duration : 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

int main()
{
	glfwInit();

	screenWidth = 1000;
	screenHeight = 1000;

	glViewport(0, 0, screenWidth, screenHeight);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Tank Simulation - early early alpha version", NULL, NULL);
	if (window != NULL)
	{
		initialize(window);

		//creating models
		cz = new Czolg();
		terrain = new Model("teren.txt", "grassTex.png");
		bulletTemplate = new Model("bullet.obj", "metaltex.png");

		spLambert = new ShaderProgram("vertexShader.glsl", NULL, "fragmentShader.glsl");
		spParticle = new ShaderProgram("vParticleShader.glsl", NULL, "fParticleShader.glsl");

		renderLoop(window);
	}
	else printf("Sumfing went wrong\n");

	delete cz;
	delete spLambert;
	delete spParticle;
	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate();
	system("pause");
	return 0;
}