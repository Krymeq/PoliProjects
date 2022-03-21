#version 330

//Zmienne jednorodne
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Atrybuty
layout (location = 0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec3 aNormal; //wspolrzedne wektora normalnego w przestrzeni modelu
layout (location = 2) in vec2 aTexCoord; //kolor wierzchołka

out vec2 texCoord;
out vec3 fragPosition;

void main(void) 
{
	texCoord = aTexCoord;
	fragPosition = vec3(model * vertex);
	gl_Position = projection * view * model * vertex;
}