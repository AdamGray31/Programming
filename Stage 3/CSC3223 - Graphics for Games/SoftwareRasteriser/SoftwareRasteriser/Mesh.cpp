#include "Mesh.h"

Mesh::Mesh(void)	{
	type			= PRIMITIVE_POINTS;

	numVertices		= 0;

	vertices		= NULL;
	colours			= NULL;
	textureCoords	= NULL;
}

Mesh::~Mesh(void)	{
	delete[] vertices;
	delete[] colours;
	delete[] textureCoords;
}

Mesh *Mesh::GeneratePoints(const Vector3 &point) {
	Mesh *m = new Mesh();

	m->numVertices = 1;

	m->vertices = new Vector4[m->numVertices];
	m->vertices[0] = Vector4(point.x, point.y, point.z, 1.0f);

	m->type = PRIMITIVE_POINTS;

	return m;
}

Mesh *Mesh::GenerateStarField(int numStars, int width, int height) {
	Mesh *m = new Mesh();

	m->numVertices = numStars;

	m->vertices = new Vector4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++) {
		m->vertices[i] = Vector4(rand()%(2*width) - width, rand()%(2*height) - height, -1000, 1.0f);
	}

	m->type = PRIMITIVE_POINTS;

	return m;
}

Mesh *Mesh::GenerateAsteroid() {
	Mesh *m = new Mesh();

	m->numVertices = 24;
	//NumLines = numVertices/2


	m->vertices = new Vector4[m->numVertices];
	m->colours = new Colour[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];

	//Line 1
	m->vertices[0] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->vertices[1] = Vector4(0.2f, 0.9f, 0.0f, 1.0f);
	//Line 2
	m->vertices[2] = Vector4(0.2f, 0.9f, 0.0f, 1.0f);
	m->vertices[3] = Vector4(0.5f, 0.8f, 0.0f, 1.0f);
	//Line 3
	m->vertices[4] = Vector4(0.5f, 0.8f, 0.0f, 1.0f);
	m->vertices[5] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	//Line 4
	m->vertices[6] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->vertices[7] = Vector4(0.7f, -0.5f, 0.0f, 1.0f);
	//Line 5
	m->vertices[8] = Vector4(0.7f, -0.5f, 0.0f, 1.0f);
	m->vertices[9] = Vector4(0.2f, -0.7f, 0.0f, 1.0f);
	//Line 6
	m->vertices[10] = Vector4(0.2f, -0.7f, 0.0f, 1.0f);
	m->vertices[11] = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
	//Line7
	m->vertices[12] = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
	m->vertices[13] = Vector4(-0.2f, -0.8f, 0.0f, 1.0f);
	//Line8
	m->vertices[14] = Vector4(-0.2f, -0.8f, 0.0f, 1.0f);
	m->vertices[15] = Vector4(-0.6f, -0.3f, 0.0f, 1.0f);
	//Line9
	m->vertices[16] = Vector4(-0.6f, -0.3f, 0.0f, 1.0f);
	m->vertices[17] = Vector4(-1.0f, 0.0f, 0.0f, 1.0f);
	//Line10
	m->vertices[18] = Vector4(-1.0f, 0.0f, 0.0f, 1.0f);
	m->vertices[19] = Vector4(-0.5f, 0.4f, 0.0f, 1.0f);
	//Line11
	m->vertices[20] = Vector4(-0.5f, 0.4f, 0.0f, 1.0f);
	m->vertices[21] = Vector4(-0.1f, 0.7f, 0.0f, 1.0f);
	//Line12
	m->vertices[22] = Vector4(-0.1f, 0.7f, 0.0f, 1.0f);
	m->vertices[23] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);


	for (int i = 0; i < m->numVertices; i++) {
		m->colours[i] = Colour(255, 255, 255, 255);
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
	}

	m->type = PRIMITIVE_LINES;

	return m;
}

Mesh *Mesh::GenerateLine(const Vector3 &from, const Vector3 &to) {
	Mesh *m = new Mesh();

	m->numVertices = 2;
	
	m->vertices = new Vector4[m->numVertices];
	m->colours = new Colour[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];

	m->vertices[0] = Vector4(from.x, from.y, from.z, 1.0f);
	m->vertices[1] = Vector4(to.x, to.y, to.z, 1.0f);

	m->colours[0] = Colour(255, 0, 0, 255);
	m->colours[1] = Colour(0, 0, 255, 255);

	m->textureCoords[0] = Vector2(from.x, from.y);
	m->textureCoords[1] = Vector2(to.x, to.y);
	
	m->type = PRIMITIVE_LINES;
	
	return m;
	
}

Mesh *Mesh::GenerateRocket() {
	Mesh *m = new Mesh();
	
	m->numVertices = 24;

	m->vertices = new Vector4[m->numVertices];
	m->colours = new Colour[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];

	Vector4 top = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	Vector4 bottom = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
	Vector4 a = Vector4(-0.8f, -0.5f, 0.33333f, 1.0f);
	Vector4 b = Vector4(-0.8f, -0.5f, -0.33333f, 1.0f);
	Vector4 c = Vector4(0.8f, -0.5f, -0.33333f, 1.0f);
	Vector4 d = Vector4(0.8f, -0.5f, 0.33333f, 1.0f);

	m->vertices[0] = a;	
	m->vertices[1] = top;
	m->vertices[2] = b;	

	m->vertices[3] = b;	
	m->vertices[4] = top;
	m->vertices[5] = c;	

	m->vertices[6] = c;	
	m->vertices[7] = top;
	m->vertices[8] = d;	

	m->vertices[9] = d;	
	m->vertices[10] = top;
	m->vertices[11] = a;	

	m->vertices[12] = b;	
	m->vertices[13] = bottom;
	m->vertices[14] = a;	

	m->vertices[15] = c;	
	m->vertices[16] = bottom;
	m->vertices[17] = b;	

	m->vertices[18] = d;	
	m->vertices[19] = bottom;
	m->vertices[20] = c;	

	m->vertices[21] = a;	
	m->vertices[22] = bottom;
	m->vertices[23] = d;	


	//Set colours and tex coords
	Colour frontEdge = Colour(0, 0, 255, 255);
	Colour frontTip = Colour(255, 255, 255, 255);
	Colour backEdge = Colour(255, 0, 0, 255);
	Colour backTip = Colour(255, 255, 0, 255);

	for (int i = 0; i < m->numVertices; i++) {

	}

	m->colours[0] = frontEdge;
	m->colours[1] = frontTip;
	m->colours[2] = frontEdge;

	m->colours[3] = frontEdge;
	m->colours[4] = frontTip;
	m->colours[5] = frontEdge;

	m->colours[6] = frontEdge;
	m->colours[7] = frontTip;
	m->colours[8] = frontEdge;

	m->colours[9] = frontEdge;
	m->colours[10] = frontTip;
	m->colours[11] = frontEdge;

	m->colours[12] = backEdge;
	m->colours[13] = backTip;
	m->colours[14] = backEdge;

	m->colours[15] = backEdge;
	m->colours[16] = backTip;
	m->colours[17] = backEdge;

	m->colours[18] = backEdge;
	m->colours[19] = backTip;
	m->colours[20] = backEdge;

	m->colours[21] = backEdge;
	m->colours[22] = backTip;
	m->colours[23] = backEdge;


	for (uint i = 0; i < m->numVertices; i += 3) {
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
		m->textureCoords[i + 1] = Vector2(0.5f, 1.0f);
		m->textureCoords[i + 2] = Vector2(1.0f, 0.0f);
	}

	m->type = PRIMITIVE_TRIANGLES;

	return m;
}

Mesh *Mesh::GenerateTransparentRocket() {
	Mesh *m = new Mesh();

	m->numVertices = 24;

	m->vertices = new Vector4[m->numVertices];
	m->colours = new Colour[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];

	Vector4 top = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	Vector4 bottom = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
	Vector4 a = Vector4(-0.8f, -0.5f, 0.33333f, 1.0f);
	Vector4 b = Vector4(-0.8f, -0.5f, -0.33333f, 1.0f);
	Vector4 c = Vector4(0.8f, -0.5f, -0.33333f, 1.0f);
	Vector4 d = Vector4(0.8f, -0.5f, 0.33333f, 1.0f);

	m->vertices[0] = a;
	m->vertices[1] = top;
	m->vertices[2] = b;

	m->vertices[3] = b;
	m->vertices[4] = top;
	m->vertices[5] = c;

	m->vertices[6] = c;
	m->vertices[7] = top;
	m->vertices[8] = d;

	m->vertices[9] = d;
	m->vertices[10] = top;
	m->vertices[11] = a;

	m->vertices[12] = b;
	m->vertices[13] = bottom;
	m->vertices[14] = a;

	m->vertices[15] = c;
	m->vertices[16] = bottom;
	m->vertices[17] = b;

	m->vertices[18] = d;
	m->vertices[19] = bottom;
	m->vertices[20] = c;

	m->vertices[21] = a;
	m->vertices[22] = bottom;
	m->vertices[23] = d;


	//Set colours and tex coords
	Colour frontEdge = Colour(0, 0, 255, 127);
	Colour frontTip = Colour(255, 255, 255, 127);
	Colour backEdge = Colour(255, 0, 0, 127);
	Colour backTip = Colour(255, 255, 0, 127);

	for (int i = 0; i < m->numVertices; i++) {

	}

	m->colours[0] = frontEdge;
	m->colours[1] = frontTip;
	m->colours[2] = frontEdge;

	m->colours[3] = frontEdge;
	m->colours[4] = frontTip;
	m->colours[5] = frontEdge;

	m->colours[6] = frontEdge;
	m->colours[7] = frontTip;
	m->colours[8] = frontEdge;

	m->colours[9] = frontEdge;
	m->colours[10] = frontTip;
	m->colours[11] = frontEdge;

	m->colours[12] = backEdge;
	m->colours[13] = backTip;
	m->colours[14] = backEdge;

	m->colours[15] = backEdge;
	m->colours[16] = backTip;
	m->colours[17] = backEdge;

	m->colours[18] = backEdge;
	m->colours[19] = backTip;
	m->colours[20] = backEdge;

	m->colours[21] = backEdge;
	m->colours[22] = backTip;
	m->colours[23] = backEdge;


	for (uint i = 0; i < m->numVertices; i += 3) {
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
		m->textureCoords[i + 1] = Vector2(0.5f, 1.0f);
		m->textureCoords[i + 2] = Vector2(1.0f, 0.0f);
	}

	m->type = PRIMITIVE_TRIANGLES;

	return m;
}

Mesh *Mesh::GenerateTriangle() {
	Mesh *m = new Mesh();
	m->type = PRIMITIVE_TRIANGLES;

	m->numVertices = 3;
	
	m->vertices = new Vector4[m->numVertices];
	m->colours = new Colour[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];

	m->vertices[0] = Vector4(0.5f, -0.5f, 0, 1.0f);
	m->vertices[1] = Vector4(0.0f, 0.5f, 0, 1.0f);
	m->vertices[2] = Vector4(-0.5f, -0.5f, 0, 1.0f);

	m->colours[0] = Colour(255, 0, 0, 255);
	m->colours[1] = Colour(0, 255, 0, 255);
	m->colours[2] = Colour(0, 0, 255, 255);

	m->textureCoords[0] = Vector2(0.0f, 0.0f);
	m->textureCoords[1] = Vector2(0.5f, 1.0f);
	m->textureCoords[2] = Vector2(1.0f, 0.0f);


	return m;

}

Mesh *Mesh::LoadMeshFile(const string &filename) {
	ifstream f(filename);

	if (!f) {
		return NULL;

	}

	Mesh *m = new Mesh();
	m->type = PRIMITIVE_TRIANGLES;
	f >> m -> numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex; // Oooh ! Sneak preview of later tutorial ...
	f >> hasColour;

	m->vertices = new Vector4[m -> numVertices];
	m->textureCoords = new Vector2[m -> numVertices];
	m->colours = new Colour[m -> numVertices];

	for (uint i = 0; i < m -> numVertices; ++i) {
		f >> m -> vertices[i].x;
		f >> m -> vertices[i].y;
		f >> m -> vertices[i].z;

	}
	if (hasColour) {
		for (uint i = 0; i < m -> numVertices; ++i) {
			f >> m -> colours[i].r; f >> m -> colours[i].g;
			f >> m -> colours[i].b; f >> m -> colours[i].a;

		}

	}
	if (hasTex) {
		for (uint i = 0; i < m->numVertices; ++i) {
			f >> m->textureCoords[i].x;
			f >> m->textureCoords[i].y;
		}
	}
	return m;
}