#version 330

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPosition;
out vec3 normal;
out vec2 texCoord;

void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	fragPosition = vec3(model * aPos);

	texCoord = aTexCoord;

    gl_Position = projection * view * model * aPos;
}