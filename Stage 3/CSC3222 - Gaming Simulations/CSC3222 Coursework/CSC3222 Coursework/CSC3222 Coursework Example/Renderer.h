#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/SceneNode.h"
#include "../nclgl/Frustum.h"
#include <algorithm>
#include "Physics.h"


class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent, Physics* p);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

	Physics* p;

protected:
	void	BuildNodeLists(SceneNode* from);
	void	SortNodeLists();
	void	ClearNodeLists();
	void	DrawNodes();
	void	DrawNode(SceneNode*n);

	SceneNode* root;
	Camera*	camera;
	Mesh*	map;
	Mesh*	raider;
	Mesh*	arrow;
	Mesh*	leader;
	Mesh*	dragon;
	Mesh*	breathWeapon;

	Frustum frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;
};

