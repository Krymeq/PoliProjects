#version 330


//Zmienne interpolowane
in vec2 texCoord;
in vec3 fragPosition;

uniform vec3 viewPosition;
uniform sampler2D tex;

out vec4 fragColor;

void main(void) {
	
	//calculating the fog
	float dist = distance(viewPosition, fragPosition) - 15.0f;
	float density = 0.02f;
	float fogFactor = 1 / exp(pow((dist * density), 2));
	vec4 fogColor = vec4(0.6f, 0.9f, 1.0f, 1.0f);

	vec4 pixelColor = 0.8f * texture(tex, texCoord);
	fragColor = mix(fogColor, pixelColor, fogFactor);
}