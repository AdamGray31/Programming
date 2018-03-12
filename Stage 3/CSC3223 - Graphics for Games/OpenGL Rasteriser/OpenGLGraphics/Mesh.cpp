#include "Mesh.h"

Mesh::Mesh(void)	{
	//Most objects in OpenGL are represented as 'names' - an unsigned int
	//index, really. They are always generated and destroyed by OpenGL 
	//functions. Most of these functions allow you to generate multiple
	//names at once (the first parameter here is a count).
	glGenVertexArrays(1, &arrayObject);
	
	for(int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}

	numVertices  = 0;
	type		 = GL_TRIANGLES;

	//Later tutorial stuff
	numIndices    = 0;
	vertices	  = NULL;
	textureCoords = NULL;
	normals		  = NULL;
	tangents	  = NULL;
	indices		  = NULL;
	colours		  = NULL;
}

Mesh::~Mesh(void)	{
	glDeleteVertexArrays(1, &arrayObject);			//Delete our VAO
	glDeleteBuffers(MAX_BUFFER, bufferObject);		//Delete our VBOs

	//Later tutorial stuff
	delete[]vertices;
	delete[]indices;
	delete[]textureCoords;
	delete[]tangents;
	delete[]normals;
	delete[]colours;
}

void Mesh::Draw()	{
	/*
	To render with a mesh in OpenGL, we need to bind all of the buffers
	containing vertex data to the pipeline, and attach them to the
	generic attributes referenced in our vertex shader.
	That's quite a lot of code to set up, but fear not - all of the state
	is cached within our Vertex Array Object, so once that's been set up
	by the BufferData function, all we need to do is bind the VAO and it
	all happens automagically
	*/
	glBindVertexArray(arrayObject);
	//There are two draw functions in OpenGL, depending on whether we're 
	//using indices or not. Both start off taking a primitive type - 
	//triangles, quads, lines, points etc. 

	if(bufferObject[INDEX_BUFFER]) {
		/*
		If we have an index buffer, we tell OpenGL how to parse that
		buffer data (is it bytes/ints/shorts), and how many data
		elements there are. The last parameter should nearly always be 0,
		it's part of the old OpenGL spec.
		*/
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else{
		/*
		If we don't have indices, we can just use this function.
		Its extra parameters define which is the first vertex
		to draw, and how many vertices past this point to draw.
		*/
		glDrawArrays(type, 0, numVertices);	//Draw the triangle!
	}
	/*
	We don't strictly have to do this, but 'undoing' whatever
	we do to OpenGL in a function generally keeps the pipeline
	from getting incorrect states, or otherwise not doing what
	you want it to do.
	*/
	glBindVertexArray(0);	
}

Mesh* Mesh::GenerateTriangle()	{
	Mesh*m = new Mesh();
	m->numVertices = 3;

	m->vertices		= new Vector3[m->numVertices];
	m->vertices[0]	= Vector3(0.0f,	0.5f,	0.0f);
	m->vertices[1]	= Vector3(0.5f,  -0.5f,	0.0f);
	m->vertices[2]	= Vector3(-0.5f, -0.5f,	0.0f);

	m->textureCoords	= new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f,	0.0f);
	m->textureCoords[1] = Vector2(1.0f,	1.0f);
	m->textureCoords[2] = Vector2(0.0f,	1.0f);

	m->colours		= new Vector4[m->numVertices];
	m->colours[0]	= Vector4(1.0f, 0.0f, 0.0f,1.0f); 
	m->colours[1]	= Vector4(0.0f, 1.0f, 0.0f,1.0f);
	m->colours[2]	= Vector4(0.0f, 0.0f, 1.0f,1.0f);

	m->GenerateNormals();
	m->BufferData();
	

	return m;
}

Mesh* Mesh::GenerateCube() {
	Mesh*m = new Mesh();
	m->numVertices = 36;

	m->vertices = new Vector3[m->numVertices];	
	
	Vector3 ltb, rtb, ltf, rtf, lbb, rbb, lbf, rbf; //LeftTopBack,...,RightBottomFront
	ltb = Vector3(-1.0f, 1.0f, -1.0f);
	rtb = Vector3(1.0f, 1.0f, -1.0f);
	ltf = Vector3(-1.0f, 1.0f, 1.0f);
	rtf = Vector3(1.0f, 1.0f, 1.0f);
	lbb = Vector3(-1.0f, -1.0f, -1.0f);
	rbb = Vector3(1.0f, -1.0f, -1.0f);
	lbf = Vector3(-1.0f, -1.0f, 1.0f);
	rbf = Vector3(1.0f, -1.0f, 1.0f);

	m->vertices = new Vector3[m->numVertices];
	//Back face 
	m->vertices[0] = rtb;
	m->vertices[1] = ltb;
	m->vertices[2] = rbb;
	m->vertices[3] = rbb;
	m->vertices[4] = ltb;
	m->vertices[5] = lbb;
	//Top face
	m->vertices[6] = ltb;
	m->vertices[7] = rtb;
	m->vertices[8] = ltf;
	m->vertices[9] = ltf;
	m->vertices[10] = rtb;
	m->vertices[11] = rtf;
	//Left face
	m->vertices[12] = ltb;
	m->vertices[13] = ltf;
	m->vertices[14] = lbb;
	m->vertices[15] = lbb;
	m->vertices[16] = ltf;
	m->vertices[17] = lbf;
	//Right face
	m->vertices[18] = rtf;
	m->vertices[19] = rtb;
	m->vertices[20] = rbf;
	m->vertices[21] = rbf;
	m->vertices[22] = rtb;
	m->vertices[23] = rbb;
	//Bottom face
	m->vertices[24] = lbf;
	m->vertices[25] = rbf;
	m->vertices[26] = lbb;
	m->vertices[27] = lbb;
	m->vertices[28] = rbf;
	m->vertices[29] = rbb;
	//Front face
	m->vertices[30] = ltf;
	m->vertices[31] = rtf;
	m->vertices[32] = lbf;
	m->vertices[33] = lbf;
	m->vertices[34] = rtf;
	m->vertices[35] = rbf;


	m->textureCoords = new Vector2[m->numVertices];

	for (int i = 0; i < m->numVertices; i += 6) {
		m->textureCoords[i] =	  Vector2(0.0f, 0.0f);
		m->textureCoords[i + 1] = Vector2(1.0f, 0.0f);
		m->textureCoords[i + 2] = Vector2(0.0f, 1.0f);
		m->textureCoords[i + 3] = Vector2(0.0f, 1.0f);
		m->textureCoords[i + 4] = Vector2(1.0f, 0.0f);
		m->textureCoords[i + 5] = Vector2(1.0f, 1.0f);
	}


	m->colours = new Vector4[m->numVertices];
	//Right Top Back
	m->colours[0] =	Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[7] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[10] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[19] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[22] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	//Left Top Back
	m->colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[4] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[6] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[12] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	//Right Bottom Back
	m->colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	m->colours[3] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	m->colours[23] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	m->colours[29] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	
	//Left Bottom Back
	m->colours[5] = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	m->colours[14] = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	m->colours[15] = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	m->colours[26] = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	m->colours[27] = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	
	//Left Top Front
	m->colours[8] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	m->colours[9] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	m->colours[13] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	m->colours[16] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	m->colours[30] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

	//Right Top Front
	m->colours[11] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
	m->colours[18] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
	m->colours[31] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
	m->colours[34] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);

	//Left Bottom Front
	m->colours[17] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	m->colours[24] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	m->colours[32] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	m->colours[33] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

	//Right Bottom Front
	m->colours[20] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->colours[21] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->colours[25] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->colours[28] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->colours[35] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	
	m->GenerateNormals();
	m->BufferData();
	
	return m;

}

Mesh* Mesh::GeneratePoints(unsigned int count) {
	Mesh *m = new Mesh();
	m->numVertices = count;
	m->vertices = new Vector3[m->numVertices];
	m->colours = new Vector4[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->type = GL_POINTS;

	for (int i = 0; i < m->numVertices; ++i) {
		float x = (float)(rand() % 100 - 50);
		float y = (float)(rand() % 100 - 50);
		float z = (float)(rand() % 100 - 50);
		m->vertices[i] = Vector3(x,y,z);
		m->colours[i] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
	}
	
	m->BufferData();

	return m;
}

Mesh* Mesh::GenerateQuadPatch() {
	Mesh* m = new Mesh();
	m -> numVertices = 4;//Number of vertices
	m -> type = GL_PATCHES;//The OpenGL render type
	
	m -> vertices = new Vector3[m -> numVertices];
	m -> textureCoords = new Vector2[m -> numVertices];
	
	m -> vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);		//TL
	m -> vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);		//BL
	m -> vertices[2] = Vector3(1.0f, -1.0f, 0.0f);		//TR
	m -> vertices[3] = Vector3(1.0f, 1.0f, 0.0f);		//Not being rendered
	
	m -> textureCoords[0] = Vector2(0.0f, 1.0f);
	m -> textureCoords[1] = Vector2(0.0f, 0.0f);
	m -> textureCoords[2] = Vector2(1.0f, 1.0f);
	m -> textureCoords[3] = Vector2(1.0f, 0.0f);

	m -> BufferData();//Function containing all of the VAO and VBO setup
	
	return m;
}

Mesh*	Mesh::LoadMeshFile(const string &filename) {
	ifstream f(filename);

	if(!f) {
		return NULL;
	}

	Mesh*m = new Mesh();
	f >> m->numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex;
	f >> hasColour;

	m->vertices = new Vector3[m->numVertices];

	if(hasTex) {
		m->textureCoords = new Vector2[m->numVertices];
		m->colours		 = new Vector4[m->numVertices];
	}

	for (unsigned int i = 0; i < m->numVertices; ++i) {
		f >> m->vertices[i].x;
		f >> m->vertices[i].y;
		f >> m->vertices[i].z;
	}

	if (hasColour) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			unsigned char r, g, b, a;

			f >> r;
			f >> g;
			f >> b;
			f >> a;
			//OpenGL can use floats for colours directly - this will take up 4x as
			//much space, but could avoid any byte / float conversions happening
			//behind the scenes in our shader executions
			m->colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
	}

	if (hasTex) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			f >> m->textureCoords[i].x;
			f >> m->textureCoords[i].y;
		}
	}
	m->GenerateNormals();
	m->BufferData();
	return m;
}

void Mesh::GenerateNormals() {
	if (!normals) {
		normals = new Vector3[numVertices];
	}
	for (unsigned int i = 0; i < numVertices; i += 3) {
		Vector3 &a = vertices[i + 2];
		Vector3 &b = vertices[i + 1];
		Vector3 &c = vertices[i];

		Vector3 normal = Vector3::Cross(b - a, c - a);
		normal.Normalise();

		normals[i]		= normal;
		normals[i + 1]	= normal;
		normals[i + 2]	= normal;
	}
}

void	Mesh::BufferData()	{
	/*
		To more efficiently bind and unbind the states required to draw a mesh,
		we can encapsulate them all inside a Vertex Array Object.

		When a VAO is bound, all further changes to vertex buffers and vertex
		attributes are cached inside the VAO, and will be reapplied whenever
		that VAO is later bound again
	*/
	glBindVertexArray(arrayObject);

	/*
	To put some vertex data on the GPU, we must create a buffer object to store it.

	To upload data to a vertex buffer, it must be bound, with a specific 'target',
	which defines what the buffer is to be used for.

	Then, once bound, data can be uploaded using the glBufferData function, which
	takes a pointer to the data to be sent, and the size of that data, as well as
	a usage parameter - this lets OpenGL know how the data will be accessed.

	To turn a vertex buffer into a vertex attribute suitable for sending to a
	vertex shader, the glVertexAttribPointer function must be called. 
	This takes in an attribute 'slot', how many elements each data entry has
	(i.e 2 for a vector2 etc), and what datatype (usually float) it is.
	This will bind the currently bound vertex buffer to that attribute slot.
	To actually enable that attribute slot, the glEnableVertexAttribArray is called.

	Note that we use the value VERTEX_BUFFER for the 'slot' parameter - this is just
	an enum value, that equates to 0. It's common to use enums as indices into arrays
	in this way, as it keeps everything consistent. It's also pretty sensible to always
	bind the same data types to the same attribute slots, it makes life much easier!

	These last two functions, along with the glBindBuffer call, are examples of 
	functionality that is cached in the actual VAO.
	*/

	//Buffer vertex data
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(VERTEX_BUFFER);

	////Buffer texture data
	if (textureCoords) {
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	//buffer colour data
	if (colours)	{
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector4), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	//buffer index data
	if(indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	if (normals) {
		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), normals, GL_STATIC_DRAW);

		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	//Once we're done with the vertex buffer binding, we can unbind the VAO,
	//ready to reapply later, such as in the Draw function above!
	glBindVertexArray(0);
}

