#version 330 core

uniform float time;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in Vertex {
	vec2 texCoord;
	vec4 colour;
} IN[];

out Vertex {
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void) {
	
	float t = 2.51 - 2 * time;

	vec3 p0 = gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_in[2].gl_Position.xyz;

	vec3 v0 = p0 - p1;
	vec3 v1 = p2 - p1;

	vec3 difference = v1 - v0;

	float length = length(difference);

	vec3 n = normalize(cross(v1, v0));

	if (length > 0.001) {
		
		for (int i = 0; i < gl_in.length(); ++i) {
			
			vec4 p = gl_in[i].gl_Position;
			float len = sqrt(p.x * p.x + p.z * p.z);
			float scale = 1 + 2 * tan(0.5 * t + len);
			
			p = vec4(p.xyz + (n * 2 * scale) + (n * vec3(0.05, 0.05, 0.05)), 1.0);

			gl_Position = (projMatrix * viewMatrix * modelMatrix) * p;
			OUT.colour = IN[i].colour;
			OUT.texCoord = IN[i].texCoord;
			EmitVertex();
		}
		EndPrimitive();
	}
}