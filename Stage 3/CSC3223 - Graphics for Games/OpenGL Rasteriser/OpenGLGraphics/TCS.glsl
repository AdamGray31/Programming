#version 400 core

layout(vertices = 3) out;

in Vertex {
	vec2 texCoord;
	vec4 colour;
} IN[];

out Vertex {
	vec2 texCoord;
	vec4 colour;
} OUT[];

patch out vec4 subColour;

void main(void) {
	gl_TessLevelInner[0] = 64;

	gl_TessLevelOuter[0] = 1;
	gl_TessLevelOuter[1] = 1;
	gl_TessLevelOuter[2] = 1;

	OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}