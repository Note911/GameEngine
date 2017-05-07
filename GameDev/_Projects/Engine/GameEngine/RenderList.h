#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "Camera.h"


class RenderList {
public:
	RenderList(GLSLProgram* shader);
	~RenderList();
	//This class contains a static pointer, to a vector of pointers of each instance of this class that have been implemented.  Any instance created will be inserted into a static vector from the RenderList constructor.
	//Sort of a hacked up singleton
	static std::vector<RenderList*>* getShaderList() { 
		if (_shaderList == nullptr)
			_shaderList = new std::vector<RenderList*>();
		return _shaderList; }
	static void clearShaderList();
	static void clearAndDeleteShaderList();

	static void drawAllObjects(Camera* camera);
	//Returns a pointer to the renderlist.  Renderlist is contained on the stack and is cleared each frame. 	//NOTE: in the future we should make two implementations of this Object for both static and dynamic rendering

	std::vector<GameObject*>* getRenderList() { return _renderList; }
	GLSLProgram* getShaderProgram() { return _shaderProgram; }

	static bool containsShader(GLSLProgram* shader);
	static RenderList* getRenderListPointer(GLSLProgram* shader);

	void addObject(GameObject* gameObject);
	void drawObjects(Camera* camera);
	//A pointer to the shaderprogram used for this renderlist
	GLSLProgram* _shaderProgram;

private:
	//This vector contains pointers to each gameobject that uses a particular shader program
	static std::vector<RenderList*>* _shaderList;
	std::vector<GameObject*>* _renderList;

};
