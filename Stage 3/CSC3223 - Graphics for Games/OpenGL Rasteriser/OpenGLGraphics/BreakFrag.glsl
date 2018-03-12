#version 330 core
uniform sampler2D	tex;
uniform sampler2D	tex0;

uniform float time;

in Vertex{
	smooth vec2 texCoord;
	smooth vec4 colour;
} IN;

out vec4 fragColour;

void main(void) {
	vec4 a = texture(tex, IN.texCoord);
	vec4 b = texture(tex0, IN.texCoord);

	fragColour = a * (1 - time) + b * (time);	

}