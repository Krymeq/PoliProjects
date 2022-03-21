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

Czolg *cz;

Model *bullet;
Model *m = new Model();
Model *terrain = new Model();
ShaderProgram *spLambert;
ShaderProgram *spTerrain;
glm::mat4 translate = glm::mat4(1.0f);
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, -15.0f);
glm::vec3 cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFrontAxis = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 lightPosition = glm::vec3(25.0, 25.0, -75.0);
glm::vec3 lightColor = glm::vec3(1.0f, 0.85f, 0.75f);

std::list<Model> missiles;

short int accFactor;
int speed;
int rotateFactor;
int cannonRotation;
int screenWidth;
int screenHeight;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float cameraSpeed = 0.5f; // adjust accordingly
	
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

		if (key == GLFW_KEY_R)
		{
			cz->setTransformMatrix(glm::mat4(1.0f));
			cameraPosition = glm::vec3(0.0f, 5.0f, -15.0f);
			cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
			cameraFrontAxis = glm::vec3(0.0f, -0.3f, 1.0f);
		}
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
		cameraPosition = glm::vec3(tankPos.x - 15 * sin(glm::radians(a)), 5, tankPos.z - 15 * cos(glm::radians(a)));
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

		bullet->draw(spLambert, viewMatrix, projectionMatrix);
		cz->draw(spLambert, viewMatrix, projectionMatrix);
		terrain->draw(spTerrain, viewMatrix, projectionMatrix);

		auto stop = std::chrono::steady_clock::now();
		float duration = 1000.0f/60.0f - std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

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

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "jakies okienko", NULL, NULL);
	if (window != NULL)
	{
		initialize(window);

		//creating models
		cz = new Czolg();
		terrain = new Model("teren.txt", "grassTex.png");
		bullet = new Model("bullet.obj", "metaltex.png");

		spLambert = new ShaderProgram("vertexShader.glsl", NULL, "fragmentShader.glsl");
		spTerrain = new ShaderProgram("vertex2.glsl", NULL, "fragment2.glsl");

		renderLoop(window);
	}
	else printf("Sumfing went wrong\n");

	delete m;
	delete spLambert;
	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate();
	system("pause");
	return 0;
}