#pragma once
#include "Model.h"
class Czolg
{
private:
	Model *hull;
	Model *turret;
	Model *gun;
	Model *trackLeft;
	Model *trackRight;
	Model *wheelsLeft;
	Model *wheelsRight;
	//Translation matrix of the whole tank
	glm::mat4 position;
	//turret's rotation angle
	float angle;
public:
	Czolg();

	glm::vec3 getTurretPosition();

	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 vector);
	void scale(glm::vec3 scalingFactor);
	void draw(ShaderProgram* sp, glm::mat4 v, glm::mat4 p);
	void setTransformMatrix(glm::mat4 position);
	void rotateTurret(float angle);

	float getAngle();
	~Czolg();
};

