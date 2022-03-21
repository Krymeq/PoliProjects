#include "Czolg.h"

Czolg::Czolg()
{
	this->angle = 0.0f;
	this->position = glm::mat4(1.0f);
	this->hull = new Model("tank/HULL.obj", "Texture.png");
	this->turret = new Model("tank/TURRET.obj", "Texture.png");
	this->gun = new Model("tank/GUN.obj", "Texture.png");
	this->trackLeft = new Model("tank/LEFT_TRACK.obj", "tankTexture.png");
	this->trackRight = new Model("tank/RIGHT_TRACK.obj", "tankTexture.png");
	this->wheelsLeft = new Model("tank/LEFT_WHEELS.obj", "tankTexture.png");
	this->wheelsRight = new Model("tank/RIGHT_WHEELS.obj", "tankTexture.png");
}

void Czolg::draw(ShaderProgram* sp, glm::mat4 v, glm::mat4 p)
{
	this->hull->draw(sp, v, p, this->position);
	this->turret->draw(sp, v, p, this->position);
	this->gun->draw(sp, v, p, this->position);
	this->trackLeft->draw(sp, v, p, this->position);
	this->trackRight->draw(sp, v, p, this->position);
	this->wheelsLeft->draw(sp, v, p, this->position);
	this->wheelsRight->draw(sp, v, p, this->position);
}

glm::vec3 Czolg::getTurretPosition()
{
	return glm::vec3(this->position[3][0], this->position[3][1], this->position[3][2]);
}

void Czolg::rotate(float angle, glm::vec3 axis)
{
	this->angle += angle;
	this->position = glm::rotate(this->position, glm::radians(angle), axis);
}

void Czolg::translate(glm::vec3 vector)
{
	this->position = glm::translate(this->position, vector);
}

void Czolg::scale(glm::vec3 scalingFactor)
{
	this->position = glm::scale(this->position, scalingFactor);
}

void Czolg::setTransformMatrix(glm::mat4 position)
{
	this->angle = 0.0f;
	this->position = position;
	this->hull->setTransformMatrix(position);
	this->turret->setTransformMatrix(position);
	this->gun->setTransformMatrix(position);
	this->trackLeft->setTransformMatrix(position);
	this->trackRight->setTransformMatrix(position);
	this->wheelsLeft->setTransformMatrix(position);
	this->wheelsRight->setTransformMatrix(position);
}

void Czolg::rotateTurret(float angle)
{
	this->angle += angle;
	this->turret->rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	this->gun->rotate(angle, glm::vec3(0.0, 1.0, 0.0));
}

float Czolg::getAngle()
{
	return this->angle;
}

Czolg::~Czolg()
{
	delete hull;
	delete turret;
	delete gun;
	delete trackLeft;
	delete trackRight;
	delete wheelsLeft;
	delete wheelsRight;
}
