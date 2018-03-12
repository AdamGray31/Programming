#pragma once
#include "../nclgl/OGLRenderer.h"

#include "RenderObject.h"

#include <vector>

using std::vector;

struct Light {
	Vector3 position;
	float radius;
	Vector3 colour;
};

class Renderer : public OGLRenderer	{

public:

	float time;
	GLuint brickTex;
	GLuint brokenBrickTex;
	GLuint heightMap;

	float tessLevelInner;
	float tessLevelOuter;
	

	Renderer(Window &parent);
	~Renderer(void);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void	UpdateScene(float msec);

	void			enableCulling();

	void			disableCulling();

	void	AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

	void SetShaderLight(Vector3 position, Vector3 colour, float radius) {
		currentLight.position = position;
		currentLight.colour = colour;
		currentLight.radius = radius;
	}

protected:
	vector<RenderObject*> renderObjects;
	Light currentLight;

	void ApplyShaderLight(GLuint program) {
		glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, (float *)&(currentLight.position));
		glUniform3fv(glGetUniformLocation(program, "lightColour"), 1, (float *)&(currentLight.colour));
		glUniform1f(glGetUniformLocation(program, "lightRadius"), currentLight.radius);
	}
	
};

