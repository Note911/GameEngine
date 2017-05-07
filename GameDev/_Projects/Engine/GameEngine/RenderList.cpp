#include "RenderList.h"

std::vector<RenderList*>* RenderList::_shaderList = nullptr;

RenderList::RenderList(GLSLProgram* shader) {
	_shaderProgram = shader;
	_renderList = new std::vector<GameObject*>();
	if (_shaderList == nullptr)
		_shaderList = new std::vector<RenderList*>();
	_shaderList->push_back(this);
}

RenderList::~RenderList() {
	_shaderProgram = nullptr;
	_renderList = nullptr;
}

void RenderList::clearShaderList() {
	for (std::vector<RenderList*>::iterator itr = _shaderList->begin(); itr != _shaderList->end(); itr++) {
		RenderList* currentRenderList = *(RenderList**)itr._Ptr;
		if(currentRenderList->getRenderList()->size() > 0)
			currentRenderList->getRenderList()->clear();
	}
}

void RenderList::clearAndDeleteShaderList() {
	clearShaderList();
	_shaderList = nullptr;
}

bool RenderList::containsShader(GLSLProgram* shader) {
	for (std::vector<RenderList*>::iterator itr = _shaderList->begin(); itr != _shaderList->end(); itr++) {
		RenderList* rendListPtr = *(RenderList**)itr._Ptr;
		if (shader == rendListPtr->_shaderProgram)
			return true;
	}
	return false;
}

RenderList* RenderList::getRenderListPointer(GLSLProgram* shader) {
	for (std::vector<RenderList*>::iterator itr = _shaderList->begin(); itr != _shaderList->end(); itr++) {
		RenderList* rendListPtr = *(RenderList**)itr._Ptr;
		if (shader == rendListPtr->getShaderProgram())
			return rendListPtr;
	}
	return nullptr;
}

void RenderList::drawObjects(Camera* camera) {
	//responsible for calling the draw on each object and useing and unusing the shaderprogram
	
	//use the shader
	_shaderProgram->use();

	////create camera matrix transform
	GLuint pLocation = _shaderProgram->getUniformLocation("projection");
	glm::mat4 cameraMatrix = camera->getProjectionMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//iterate through the render list and call each object's draw function. from their the object will call the gameobject base draw which calls the material's draw which hooks up the attributes to the shader
		for (std::vector<GameObject*>::iterator itr = _renderList->begin(); itr != _renderList->end(); itr++) {
			GameObject* objPtr = *(GameObject**)itr._Ptr;
			objPtr->draw();
		}
	glBindTexture(GL_TEXTURE_2D, 0);
	//unuse the shader
	_shaderProgram->unuse();
}

void RenderList::drawAllObjects(Camera* camera) {

	for (std::vector<RenderList*>::iterator itr = _shaderList->begin(); itr != _shaderList->end(); itr++) {
		RenderList* rendListPtr = *(RenderList**)itr._Ptr;
		rendListPtr->drawObjects(camera);
	}
}

void RenderList::addObject(GameObject* gameObject) {
	_renderList->push_back(gameObject);
}