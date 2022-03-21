#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "lodepng.h"
#include "ShaderProgram.h"

class Model
{
public:
	Model();
	Model(Model* src);
	Model(std::string dataFile, std::string textureFile);
	~Model();

	void draw(ShaderProgram *sp, glm::mat4 v, glm::mat4 p, glm::mat4 m = glm::mat4(1.0f));

	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 vector);
	void scale(glm::vec3 scalingFactor);

	void loadFromFile(std::string path);
	void loadTexture(std::string path);
	void copyDataFromAnotherModel(Model* src);
	
	//settery i gettery
	void setNormals(std::vector<float> normalsData);
	void setTexCoords(std::vector<float> texCoordsData);
	void setVertices(std::vector<float> vertexData);
	void setTransformMatrix(glm::mat4 newMatrix);

	unsigned int getTexture();

	std::vector<float> getNormalsData();
	std::vector<float> getTexCoordData();
	std::vector<float> getVertexData();
	glm::mat4 getTransformMatrix();

private:
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<float> vertices;
	glm::mat4 transformMatrix;
	
	unsigned int texture;
};

extern glm::vec3 cameraPosition;

std::vector<float> findAllFloatNumbers(std::string text);