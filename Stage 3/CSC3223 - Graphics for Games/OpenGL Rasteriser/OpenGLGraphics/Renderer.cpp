#include "Renderer.h"

#pragma comment(lib, "nclgl.lib")

Renderer::Renderer(Window &parent):
	OGLRenderer(parent),
	time(0.0f),
	tessLevelInner(1.0f),
	tessLevelOuter(1.0f),
	brickTex(SOIL_load_OGL_texture("Brick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS)),
	brokenBrickTex(SOIL_load_OGL_texture("BrokenBrick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS)),
	heightMap(SOIL_load_OGL_texture("perlin.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS))
{
	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}

Renderer::~Renderer(void)	{
	 
}

void	Renderer::RenderScene() {

	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
}

void	Renderer::Render(const RenderObject &o) {
	modelMatrix = o.GetWorldTransform();
	
	if(o.GetShader() && o.GetMesh()) {
		
		GLuint program = o.GetShader()->GetShaderProgram();
		glUseProgram(program);
		UpdateShaderMatrices(program);
		ApplyShaderLight(program);

		//Set uniforms
		GLint location = glGetUniformLocation(program, "time");
		if (location != -1) {
			glUniform1f(location, time);
		}

		location = glGetUniformLocation(program, "tessLevelInner");
		if (location != -1) {
			glUniform1f(location, tessLevelInner);
		}

		location = glGetUniformLocation(program, "tessLevelOuter");
		if (location != -1) {
			glUniform1f(location, tessLevelOuter);
		}

		Matrix4 rotation = Matrix4(viewMatrix);
		rotation.values[12] = 0;
		rotation.values[13] = 0;
		rotation.values[14] = 0;
		rotation.values[15] = 1;
		rotation.values[3] = 0;
		rotation.values[7] = 0;
		rotation.values[11] = 0;
		Vector3 invCamPos = viewMatrix.GetPositionVector();
		Vector3 camPos = (rotation * -invCamPos);
		location = glGetUniformLocation(program, "cameraPos");
		if (location != -1) {
			glUniform3fv(location, 1, (float*)&camPos);
		}

		//Bind Textures 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, brickTex);
		GLint sampler = glGetUniformLocation(program, "tex");
		glUniform1i(sampler, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, brokenBrickTex);
		sampler = glGetUniformLocation(program, "tex0");
		glUniform1i(sampler, 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, heightMap);
		sampler = glGetUniformLocation(program, "tex1");
		glUniform1i(sampler, 2);
		


		o.Draw();
	}

	for(vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().end(); ++i ) {
		Render(*(*i));
	}
}

void	Renderer::UpdateScene(float msec) {

	//Increase time from 0 to 1
	if (time < 1.0f) {
		time += 0.0003f;
	}
	else {
		time = 0.0f;
	}


	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) {
		(*i)->Update(msec);
	}

}

void Renderer::enableCulling() {
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Renderer::disableCulling() {
	glDisable(GL_CULL_FACE);
}