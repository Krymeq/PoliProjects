﻿#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GL/glew.h"
#include "stdio.h"



class ShaderProgram {
private:
	GLuint shaderProgram; //Uchwyt reprezentuj¹cy program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentuj¹cy vertex shader
	GLuint geometryShader; //Uchwyt reprezentuj¹cy geometry shader
	GLuint fragmentShader; //Uchwyt reprezentuj¹cy fragment shader
	char* readFile(const char* fileName); //metoda wczytuj¹ca plik tekstowy do tablicy znaków
	GLuint loadShader(GLenum shaderType, const char* fileName); //Metoda wczytuje i kompiluje shader, a nastêpnie zwraca jego uchwyt
public:
	ShaderProgram(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);
	~ShaderProgram();
	void use(); //Wlacza wykorzystywanie programu cieniujacego
	GLuint u(const char* variableName); //Pobiera numer slotu zwiazanego z dana zmienna jednorodna
	GLuint a(const char* variableName); //Pobiera numer slotu zwiazanego z danym atrybutem
};
#endif
