#version 330 core
uniform sampler2D tex;

in Vertex {
	smooth vec2 texCoord;
	smooth vec4 colour;
} IN;

out vec4 fragColour;

void main(void) {
	fragColour = texture(tex, IN.texCoord);
}