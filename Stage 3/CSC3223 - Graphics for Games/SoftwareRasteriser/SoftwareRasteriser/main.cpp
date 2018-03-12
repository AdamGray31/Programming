#include "SoftwareRasteriser.h"
#include "RenderObject.h"
#include "Mesh.h"
#include "Texture.h"
#include <time.h>

int main() {
	int width = 800;
	int height = 600;

	SoftwareRasteriser r(width,height);


	//CONTROLLABLE ROCKET
	RenderObject *controllableRocket = new RenderObject();
	controllableRocket->mesh = Mesh::GenerateRocket();
	controllableRocket->modelMatrix = Matrix4::Translation(Vector3(4.0f, 4.0f, -20.0f));
	controllableRocket->modelMatrix = controllableRocket->modelMatrix *
										Matrix4::RotateY(-90.0f);
	//SEMI TRANSPARENT ROCKET
	RenderObject *semiTransparentRocket = new RenderObject();
	semiTransparentRocket->mesh = Mesh::GenerateTransparentRocket();
	semiTransparentRocket->modelMatrix = Matrix4::Translation(Vector3(0.0f, 0.0f, -20.0f));

	//STARFIELD
	RenderObject *starField = new RenderObject();
	starField->mesh = Mesh::GenerateStarField(1000, width, height);

	//ASTEROID
	RenderObject *asteroid = new RenderObject();
	asteroid->mesh = Mesh::GenerateAsteroid();
	asteroid->modelMatrix = Matrix4::Translation(Vector3(-4.0f, -4.0f, -20.0f));

	//CUBE
	RenderObject *cube = new RenderObject();
	cube->mesh = Mesh::LoadMeshFile("../NewCube.asciimesh");
	cube->texture = Texture::TextureFromTGA("../brick.tga");
	cube->modelMatrix = Matrix4::Translation(Vector3(0.0f, 0.0f, -25.0f));
	cube->modelMatrix = cube->modelMatrix * Matrix4::Rotation(45.0f, Vector3(1.0f, 1.0f, 0.0f));
	cube->modelMatrix = cube->modelMatrix * Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f));

	float aspect = (float)width / (float)height;

	Matrix4 viewMatrix;

	r.SetProjectionMatrix(Matrix4::Perspective(1.0f, 100.0f, aspect, 45.0f));

	while(r.UpdateWindow()) {
	
		//VIEWMATRIX PANNING
		if (Keyboard::KeyDown(KEY_A)) {
			viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(-0.01f, 0.0f, 0.0f));
		}
		if (Keyboard::KeyDown(KEY_D)) {
			viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.01f, 0.0f, 0.0f));
		}
		if (Keyboard::KeyDown(KEY_W)) {
			viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0f, 0.01f, 0.0f));
		}
		if (Keyboard::KeyDown(KEY_S)) {
			viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0f, -0.01f, 0.0f));
		}

		//VIEWMATRIX ZOOM
		if (Keyboard::KeyDown(KEY_PLUS)) {
			viewMatrix = viewMatrix *
				Matrix4::Translation(Vector3(0.0f, 0.0f, 0.1f));
		}
		if (Keyboard::KeyDown(KEY_MINUS)) {
			viewMatrix = viewMatrix *
				Matrix4::Translation(Vector3(0.0f, 0.0f, -0.1f));
		}		
		
		//ROCKET MOVEMENT
		if (Keyboard::KeyDown(KEY_SPACE)) {
			controllableRocket->modelMatrix = controllableRocket->modelMatrix *
				Matrix4::Translation(Vector3(0.0f, 0.01f, 0.0f));
		}
		if (Keyboard::KeyDown(KEY_DOWN)) {
			controllableRocket->modelMatrix = controllableRocket->modelMatrix *
				Matrix4::RotateY(0.5f);
		}
		if (Keyboard::KeyDown(KEY_UP)) {
			controllableRocket->modelMatrix = controllableRocket->modelMatrix *
				Matrix4::RotateY(-0.5f);
		}
		if (Keyboard::KeyDown(KEY_LEFT)) {
			controllableRocket->modelMatrix = controllableRocket->modelMatrix *
				Matrix4::RotateZ(0.5f);
		}
		if (Keyboard::KeyDown(KEY_RIGHT)) {
			controllableRocket->modelMatrix = controllableRocket->modelMatrix *
				Matrix4::RotateZ(-0.5f);
		}

		//ASTEROID ROTATION
		int currentTime = time(NULL)%360;
		float angle = -0.01 * currentTime;
		asteroid->modelMatrix = asteroid->modelMatrix *
			Matrix4::RotateZ((int)angle);


		//TRANSPARENT SHIP MOVEMENT 
		semiTransparentRocket->modelMatrix = semiTransparentRocket->modelMatrix * Matrix4::Translation(Vector3(0.0f, 0.15f, 0.0f));
		semiTransparentRocket->modelMatrix = semiTransparentRocket->modelMatrix * Matrix4::RotateY((int)angle);

		r.SetViewMatrix(viewMatrix);
		
		r.ClearBuffers();



		//DRAWING FUNCTIONS
		r.DrawObject(starField);
		r.DrawObject(controllableRocket);
		r.DrawObject(asteroid);
		r.DrawObject(cube);
		r.DrawObject(semiTransparentRocket);



		r.SwapBuffers();



		//SAMPLING
		if (Keyboard::KeyDown(KEY_NUMPAD1)) {
			r.SwitchTextureFiltering(SAMPLE_BILINEAR);
		}
		if (Keyboard::KeyDown(KEY_NUMPAD2)) {
			r.SwitchTextureFiltering(SAMPLE_NEAREST);
		}
		if (Keyboard::KeyDown(KEY_NUMPAD3)) {
			r.SwitchTextureFiltering(SAMPLE_MIPMAP_BILINEAR);
		}
		if (Keyboard::KeyDown(KEY_NUMPAD4)) {
			r.SwitchTextureFiltering(SAMPLE_MIPMAP_NEAREST);
		}
		
		//QUIT
		if (Keyboard::KeyDown(KEY_ESCAPE)) {
			break;
		}

	}

	delete controllableRocket->mesh, starField->mesh, asteroid->mesh, cube->mesh, semiTransparentRocket->mesh,
		controllableRocket, starField, asteroid, cube, semiTransparentRocket;
	
	return 0;
}