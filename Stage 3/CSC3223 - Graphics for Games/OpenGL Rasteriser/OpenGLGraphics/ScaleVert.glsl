#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform float time;

in  vec3 position;
in  vec2 texCoord;
in  vec4 colour;

out Vertex{
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void) {

	float s = 1 - time;
	gl_Position = (projMatrix * viewMatrix * modelMatrix)  
					* mat4(
							vec4(s, 0, 0, 0),
							vec4(0, s, 0, 0),
							vec4(0, 0, s, 0),
							vec4(0, 0, 0, 1)
							)
							* vec4(position, 1.0);

	OUT.texCoord = texCoord;
	OUT.colour = colour;

}