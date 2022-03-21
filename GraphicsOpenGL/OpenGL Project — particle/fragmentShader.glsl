#version 330

out vec4 FragColor;

in vec3 normal;
in vec3 fragPosition;
in vec2 texCoord;

uniform vec3 viewPosition;

uniform sampler2D tex;

void main()
{
	vec3 lightPosition = vec3(25.0, 25.0, -75.0);
	vec3 lightColor = vec3(1.0, 0.9, 0.8);
	
	// Ambient lighting setup
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse lighting setup 
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPosition);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular lighting setup
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect (-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	//calculating the fog
	float dist = distance(viewPosition, fragPosition) - 15.0f;
	float density = 0.02f;
	float fogFactor = 1 / exp(pow((dist * density), 2));
	vec4 fogColor = vec4(0.6f, 0.9f, 1.0f, 1.0f);


	//calculating result
	vec4 actualColor = vec4((ambient + diffuse + specular), 1.0) * texture(tex, texCoord);
	FragColor = mix(fogColor, actualColor, fogFactor);
}