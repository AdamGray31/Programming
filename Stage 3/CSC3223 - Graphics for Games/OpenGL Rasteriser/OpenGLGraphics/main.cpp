#include "Renderer.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")

void main(void) {

	Window w = Window(800, 600);
	Renderer r(w);

	//Declar number of shaders and an array of them
	const int SHADER_COUNT = 7;
	Shader* shaders[SHADER_COUNT];

	//Declare shader names
	int basic = 0;
	int shrink = 1;
	int broken = 2;
	int fade = 3;
	int explode = 4;
	int tess = 5;
	int lighting = 6;

	//Reset shaders to null
	for (int i = 0; i < SHADER_COUNT; ++i) {
		shaders[i] = NULL;
	}

	//Load in new shaders
	shaders[basic] = new Shader("BasicVert.glsl", "TextureFrag.glsl");
	shaders[shrink] = new Shader("ScaleVert.glsl", "TextureFrag.glsl");
	shaders[broken] = new Shader("BasicVert.glsl", "BreakFrag.glsl");
	shaders[fade] = new Shader("BasicVert.glsl", "FadeFrag.glsl");
	shaders[explode] = new Shader("NoMVPVert.glsl", "TextureFrag.glsl", "ExplosionGeom.glsl");
	shaders[tess] = new Shader("NoMVPVert.glsl", "TextureFrag.glsl", "", "TCS.glsl", "TES.glsl");
	shaders[lighting] = new Shader("LightingVert.glsl", "phong.glsl"); //Tried this with Tesselated cube but it didn't work, only ambient light was applied. Needed a geometry shader, didn't have time to implement 

	//Add Cube Object to scene
	Mesh* cubeMesh = Mesh::GenerateCube();
	RenderObject cube(cubeMesh, shaders[basic]);
	r.AddRenderObject(cube);

	//Set projection matrix to perspective
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));

	//Set ViewMatrix
	Matrix4 viewMatrix = Matrix4::BuildViewMatrix(Vector3(0, 0, 10), Vector3(0, 0, -10));
	r.SetViewMatrix(viewMatrix);

	//Set Lighting
	r.SetShaderLight(Vector3(10.0f, 5.0f, 0.0f), Vector3(1, 0, 0), 1000.0f);

	Matrix4 cubeModel = cube.GetModelMatrix();

	//Display controls
	std::cout << "\n\n\n"
		<< "Controls:\n"
		<< "W, A, S, D to pan the screen\n"
		<< "Arrow keys to rotate cube\n"
		<< "+ and - to zoom in and out.\n"
		<< "Numpad 0 - "<< SHADER_COUNT-1 <<" to change shader\n\n"
		<< "Shaders:\n"
		<< "0: default\n"
		<< "1: shrink\n"
		<< "2: broken\n"
		<< "3: fade\n"
		<< "4: explode\n"
		<< "5: tesselate\n"
		<< "6: red lighting\n"
		;

	//r.enableCulling();

	while (w.UpdateWindow()) {
		float msec = w.GetTimer()->GetTimedMS();

		//ViewMatrix Panning
		if (Keyboard::KeyDown(KEY_A)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0.5f, 0, 0));
		}
		if (Keyboard::KeyDown(KEY_D)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(-0.5f, 0, 0));
		}
		if (Keyboard::KeyDown(KEY_S)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, 0.5f, 0));
		}
		if (Keyboard::KeyDown(KEY_W)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, -0.5f, 0));
		}
		if (Keyboard::KeyDown(KEY_MINUS)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, 0, -0.5f));
		}
		if (Keyboard::KeyDown(KEY_PLUS)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, 0, 0.5f));
		}

		//Cube rotation
		if (Keyboard::KeyDown(KEY_UP)) {
			cubeModel = cubeModel * Matrix4::Rotation(msec * 0.05f, Vector3(1, 0, 0));
		}
		if (Keyboard::KeyDown(KEY_DOWN)) {
			cubeModel = cubeModel * Matrix4::Rotation(msec * 0.05f, Vector3(-1, 0, 0));
		}
		if (Keyboard::KeyDown(KEY_LEFT)) {
			cubeModel = cubeModel * Matrix4::Rotation(msec * 0.05f, Vector3(0, 1, 0));
		}
		if (Keyboard::KeyDown(KEY_RIGHT)) {
			cubeModel = cubeModel * Matrix4::Rotation(msec * 0.05f, Vector3(0, -1, 0));
		}

		//Set to basic shader
		if (Keyboard::KeyDown(KEY_NUMPAD0)) {
			r.enableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[basic]);
		}

		//Set to shrink shader
		if (Keyboard::KeyDown(KEY_NUMPAD1)) {
			r.enableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[shrink]);
		}

		//Set to break shader
		if (Keyboard::KeyDown(KEY_NUMPAD2)) {
			r.enableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[broken]);
		}

		//Set to fade shader
		if (Keyboard::KeyDown(KEY_NUMPAD3)) {
			r.enableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[fade]);
		}

		//Set to explode shader
		if (Keyboard::KeyDown(KEY_NUMPAD4)) {
			r.disableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[explode]);
		}

		//Set to tesselation shader
		if (Keyboard::KeyDown(KEY_NUMPAD5)) {
			r.disableCulling();
			cubeMesh->type = GL_PATCHES;
			r.time = 0.0f;
			cube.SetShader(shaders[tess]);
		}

		//Set to lighting shader
		if (Keyboard::KeyDown(KEY_NUMPAD6)) {
			r.enableCulling();
			cubeMesh->type = GL_TRIANGLES;
			r.time = 0.0f;
			cube.SetShader(shaders[lighting]);
		}

		//Set ViewMatrix and ModelMatrix
		cube.SetModelMatrix(cubeModel);
		r.SetViewMatrix(viewMatrix);
		
		//Draw the scene
		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
		
		//Quit
		if (Keyboard::KeyDown(KEY_ESCAPE)) {
			break;
		}

	}

	for (int i = 0; i < SHADER_COUNT; ++i) {
		if (shaders[i] != NULL) {
			delete shaders[i];
		}
		shaders[i] = NULL;
	}
	delete cubeMesh;
}

