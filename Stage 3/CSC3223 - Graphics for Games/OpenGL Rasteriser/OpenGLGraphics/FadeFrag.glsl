#version 330 core

uniform sampler2D	tex;

uniform float time;

in Vertex {
	smooth vec2 texCoord;
	smooth vec4 colour;
} IN;

out vec4 fragColour;

void main(void) {
	vec4 a = texture(tex, IN.texCoord);
	fragColour = a * (1 - time) + vec4(0, 0, 0, 0);
}