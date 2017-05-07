#include "GameObject.h"
#include "Vertex.h"

GameObject::GameObject() {
	init(glm::vec3(0, 0, 0), glm::vec4(0, 0, 0, 1), glm::vec3(1, 1, 1));
	_material = nullptr;
}

GameObject::~GameObject(){}

void GameObject::init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale) {
	_transform.setPosition(position);
	_transform.setRotation(rotation);
	_transform.setScale(scale);
}

void GameObject::update(glm::mat4 parentMatrix) {
	_needsMatrixUpdate = false;
}

void GameObject::draw() {
	if(_material != nullptr)
		_material->draw();

	//Position Vertex Attrib Pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//Color  Vertex Attrib Pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//UV attrib Pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//Normal attrib Pointer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//Model View matrix
	GLint modelViewLocation = _material->getShaderProgram()->getUniformLocation("modelview");
	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &((getTransform().getTransform()) * (getTransform().getInverse()))[0][0]);

	//Normal Matrix
	GLint normalMatLocation = _material->getShaderProgram()->getUniformLocation("normalMat");
	glUniformMatrix4fv(normalMatLocation, 1, GL_FALSE, &(getTransform().getNormal())[0][0]);
}

void GameObject::attachMaterial(Material* material) {
	_material = material;
}