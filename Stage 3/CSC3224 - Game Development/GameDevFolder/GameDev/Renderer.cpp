#include "Renderer.h"

Renderer::Renderer(Window &parent, vector<Entity*>* entities) : OGLRenderer(parent) {

	projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);
	
	camera = new Camera(0.0f, 0.0f, Vector3(0, 100, 750.0f));

	currentShader = new Shader(SHADERDIR"SceneVertex.glsl", SHADERDIR"SceneFragment.glsl");

	this->entities = entities;

	map = Mesh::GenerateQuad();

	map->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"map.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !map->GetTexture()) {
		return;
	}

	player = Mesh::GenerateQuad();

	player->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"player.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !player->GetTexture()) {
		return;
	}

	bullet = Mesh::GenerateQuad();

	bullet->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"bullet.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !bullet->GetTexture()) {
		return;
	}

	grenade = Mesh::GenerateQuad();

	grenadeTexture = SOIL_load_OGL_texture(TEXTUREDIR"grenade.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	explosionTexture = SOIL_load_OGL_texture(TEXTUREDIR"explosion.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	grenade->SetTexture(grenadeTexture);

	if (!currentShader->LinkProgram() || !grenade->GetTexture()) {
		return;
	}

	enemy = Mesh::GenerateQuad();

	enemy->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"enemy.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !enemy->GetTexture()) {
		return;
	}

	reticle = Mesh::GenerateQuad();

	reticle->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"reticle.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !reticle->GetTexture()) {
		return;
	}

	wall = Mesh::GenerateQuad();
	
	wall->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"wall.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	if (!currentShader->LinkProgram() || !wall->GetTexture()) {
		return;
	}


	root = new SceneNode();

	SceneNode * mapNode = new SceneNode();
	mapNode->SetEntity(entities->at(0));
	mapNode->SetColour(Vector4(1, 1, 1, 1));
	mapNode->SetTransform(Matrix4::Translation(Vector3(mapNode->GetEntity()->getPosition().x, mapNode->GetEntity()->getPosition().y, mapNode->GetEntity()->getDepth()))*Matrix4::Rotation(mapNode->GetEntity()->getRotation(), Vector3(0, 0, 1)));
	mapNode->SetModelScale(Vector3(864.0f, 540.0f, 100.0f));
	mapNode->SetMesh(map);
	mapNode->SetBoundingRadius(5.0f);
	root->AddChild(mapNode);

	SceneNode* playerNode = new SceneNode();
	playerNode->SetEntity(entities->at(1));
	playerNode->SetColour(Vector4(1, 1, 1, 0.999));
	playerNode->SetTransform(Matrix4::Translation(Vector3(playerNode->GetEntity()->getPosition().x, playerNode->GetEntity()->getPosition().y, playerNode->GetEntity()->getDepth()))*Matrix4::Rotation(playerNode->GetEntity()->getRotation(), Vector3(0, 0, 1)));
	playerNode->SetModelScale(Vector3(10.0f, 10.0f, 1.0f));
	playerNode->SetMesh(player);
	playerNode->SetBoundingRadius(5.0f);
	root->AddChild(playerNode);

	SceneNode* playerShotNode = new SceneNode();
	playerShotNode->SetEntity(entities->at(2));
	playerShotNode->SetColour(Vector4(1, 1, 1, 0.999));
	playerShotNode->SetTransform(Matrix4::Translation(Vector3(playerShotNode->GetEntity()->getPosition().x, playerShotNode->GetEntity()->getPosition().y, playerShotNode->GetEntity()->getDepth()))*Matrix4::Rotation(playerShotNode->GetEntity()->getRotation(), Vector3(0, 0, 1)));
	playerShotNode->SetModelScale(Vector3(10.0f, 10.0f, 1.0f));
	playerShotNode->SetMesh(bullet);
	playerShotNode->SetBoundingRadius(5.0f);
	root->AddChild(playerShotNode);

	SceneNode* grenadeNode = new SceneNode();
	grenadeNode->SetEntity(entities->at(3));
	grenadeNode->SetColour(Vector4(1, 1, 1, 0.999));
	grenadeNode->SetTransform(Matrix4::Translation(Vector3(grenadeNode->GetEntity()->getPosition().x, grenadeNode->GetEntity()->getPosition().y, grenadeNode->GetEntity()->getDepth()))*Matrix4::Rotation(grenadeNode->GetEntity()->getRotation(), Vector3(0, 0, 1)));
	grenadeNode->SetModelScale(Vector3(10.0f, 10.0f, 1.0f));
	grenadeNode->SetMesh(grenade);
	grenadeNode->SetBoundingRadius(5.0f);
	root->AddChild(grenadeNode);

	SceneNode* enemyNode = new SceneNode();
	enemyNode->SetEntity(entities->at(4));
	enemyNode->SetColour(Vector4(1, 1, 1, 0.999));
	enemyNode->SetTransform(Matrix4::Translation(Vector3(enemyNode->GetEntity()->getPosition().x, enemyNode->GetEntity()->getPosition().y, enemyNode->GetEntity()->getDepth()))*Matrix4::Rotation(enemyNode->GetEntity()->getRotation(), Vector3(0, 0, 1)));
	enemyNode->SetModelScale(Vector3(10.0f, 10.0f, 1.0f));
	enemyNode->SetMesh(enemy);
	enemyNode->SetBoundingRadius(5.0f);
	root->AddChild(enemyNode);

	SceneNode* reticleNode = new SceneNode();
	Entity* ret = new Entity();
	ret->setPosition(Vector2(100, 0));
	ret->setDepth(0.5f);
	reticleNode->SetEntity(ret);
	reticleNode->SetColour(Vector4(1, 1, 1, 0.999));
	reticleNode->SetTransform(Matrix4::Translation(Vector3(ret->getPosition().x, ret->getPosition().y, ret->getDepth()))*Matrix4::Rotation(ret->getRotation(), Vector3(0, 0, 1)));
	reticleNode->SetModelScale(Vector3(10.0f, 10.0f, 1.0f));
	reticleNode->SetMesh(reticle);
	reticleNode->SetBoundingRadius(5.0f);
	playerNode->AddChild(reticleNode);

	for (int i = 0; i < 10; ++i)
	{
		SceneNode* w = new SceneNode();
		w->SetEntity(entities->at(i + 5));
		w->SetColour(Vector4(1, 1, 1, 0.999));
		w->SetTransform(Matrix4::Translation(Vector3(w->GetEntity()->getPosition().x, w->GetEntity()->getPosition().y, w->GetEntity()->getDepth()))*Matrix4::Rotation(w->GetEntity()->getRotation(), Vector3(0, 0, 1)));
		w->SetModelScale(Vector3(50.0f, 50.0f, 1.0f));
		w->SetMesh(wall);
		w->SetBoundingRadius(5.0f);
		root->AddChild(w);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init = true;
}

Renderer::~Renderer(void) {
	delete root;
	delete map;
	delete player;
	delete bullet;
	delete grenade;
	delete enemy;
	delete reticle;
	delete camera;
	delete wall;
}

void Renderer::UpdateScene(float msec, vector<Event>* events) {
	viewMatrix = camera->BuildViewMatrix();
	frameFrustum.FromMatrix(projMatrix*viewMatrix);

	root->Update(msec);


	//If there are events in the queue, check the front of it
	if (!events->empty())
	{

		//Loop through each event in the queue
		int size = events->size();
		for (int i = 0; i < size; i++)
		{
			Event &currentEvent = events->at(i);
			//Loop through the systems in the event
			for (vector<Event::system>::iterator sysIt = currentEvent.systems.begin(); sysIt != currentEvent.systems.end(); ++sysIt)
			{
				//If this system is on the systems queue, check type and act accordingly
				if (*sysIt == Event::graphics)
				{

					switch (currentEvent.eventType)
					{

					case Event::grenadeThrow:
					{
						grenade->SetTexture(grenadeTexture);
						break;
					}
					case Event::explosion:
					{
						grenade->SetTexture(explosionTexture);
						break;
					}

					}

					//Remove self from systems
					currentEvent.systems.erase(sysIt);
					break;
				}
			}

			//If no more systems on the current event, erase it
			if (currentEvent.systems.empty())
			{
				events->erase(events->begin() + i);
				--i;
				size = events->size();
			}
		}
	}

}

void Renderer::RenderScene() {
	BuildNodeLists(root);
	SortNodeLists();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	DrawNodes();

	glUseProgram(0);
	SwapBuffers();

	ClearNodeLists();
}

void	Renderer::DrawNode(SceneNode*n) {
	if (n->GetMesh()) {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, (float*)&(n->GetWorldTransform()*Matrix4::Scale(n->GetModelScale())));
		glUniform4fv(glGetUniformLocation(currentShader->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "useTexture"), (int)n->GetMesh()->GetTexture());
		GL_BREAKPOINT

			n->GetMesh()->Draw();
	}
}

void	Renderer::BuildNodeLists(SceneNode* from) {
	Vector3 direction = from->GetWorldTransform().GetPositionVector() - camera->GetPosition();
	from->SetCameraDistance(Vector3::Dot(direction, direction));

	if (frameFrustum.InsideFrustum(*from)) {
		if (from->GetColour().w < 1.0f) {
			transparentNodeList.push_back(from);
		}
		else {
			nodeList.push_back(from);
		}
	}

	for (vector<SceneNode*>::const_iterator i = from->GetChildIteratorStart(); i != from->GetChildIteratorEnd(); ++i) {
		BuildNodeLists((*i));
	}
}

void	Renderer::DrawNodes() {
	for (vector<SceneNode*>::const_iterator i = nodeList.begin(); i != nodeList.end(); ++i) {
		DrawNode((*i));
	}

	for (vector<SceneNode*>::const_reverse_iterator i = transparentNodeList.rbegin(); i != transparentNodeList.rend(); ++i) {
		DrawNode((*i));
	}
}

void	Renderer::SortNodeLists() {
	std::sort(transparentNodeList.begin(), transparentNodeList.end(), SceneNode::CompareByCameraDistance);
	std::sort(nodeList.begin(), nodeList.end(), SceneNode::CompareByCameraDistance);
}

void	Renderer::ClearNodeLists() {
	transparentNodeList.clear();
	nodeList.clear();
}