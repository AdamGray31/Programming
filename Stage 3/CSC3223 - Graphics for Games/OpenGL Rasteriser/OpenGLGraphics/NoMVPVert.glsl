#version 330 core

in  vec3 position;
in  vec2 texCoord;
in  vec4 colour;

out Vertex {
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void)	{

	OUT.texCoord	= texCoord;
	OUT.colour		= colour;

	gl_Position		= vec4(position, 1.0);

}