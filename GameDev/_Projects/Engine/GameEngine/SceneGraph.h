#pragma once
#include "Mesh.h"
#include "Sprite.h"
#include "Tree.h"
#include "RenderList.h"
#include <map>
class SceneGraph
{
public:
	SceneGraph(string rootName, GameObject* root);
	~SceneGraph();

	void addToScene(std::string key, GameObject* obj);
	void addToSceneAsChildOf(Tree::Leaf* parent, std::string key, GameObject* obj);
	void removeSprite(std::string key);
	Tree* getTree() { return _scene; }


	void clearScene();
	GameObject* find(std::string key);
	GameObject* findChildinParent(Tree::Leaf* parent, std::string key);

	void createRenderList();
	void updateScene();
private:
	Tree* _scene;
	RenderList* _renderList;
};

  