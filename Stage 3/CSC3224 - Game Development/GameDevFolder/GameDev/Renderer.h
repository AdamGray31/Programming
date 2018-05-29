#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/SceneNode.h"
#include "../nclgl/Frustum.h"
#include "Event.h"
#include <vector>
#include <algorithm>
using namespace std;

//Renderer class to render objects to a window

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent, vector<Entity*>* entities);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec, vector<Event>* events);
	virtual void RenderScene();

protected:
	void	BuildNodeLists(SceneNode* from);
	void	SortNodeLists();
	void	ClearNodeLists();
	void	DrawNodes();
	void	DrawNode(SceneNode*n);

	SceneNode* root;
	Camera*	camera;
	Mesh*	map;
	Mesh*	player;
	Mesh*	bullet;
	Mesh*	grenade;
	Mesh*	enemy;
	Mesh*	reticle;
	Mesh*	wall;

	Frustum frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	vector<Entity*>* entities;

	GLuint grenadeTexture;
	GLuint explosionTexture;

};

