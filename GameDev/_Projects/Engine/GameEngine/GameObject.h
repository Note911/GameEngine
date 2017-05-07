#pragma once
#include "Transform.h"
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "Material.h"

class GameObject {
protected:
	Transform _transform;
	Material* _material;
	GLTexture _texture;
	bool _needsMatrixUpdate = true;

public:
	GameObject();
	~GameObject();

	//getter
	Transform getTransform() { return _transform; }
	Material* getMaterial() { return _material; }
	bool needsUpdate() { return _needsMatrixUpdate; }
	
	void virtual init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	void virtual update(glm::mat4 parentMatrix);
	void virtual draw();

	void attachMaterial(Material* material);

	//setters
	void setPosition(glm::vec3 position) { _transform.setPosition(position); _needsMatrixUpdate = true; }
	void translate(glm::vec3 trans) { _transform.translate(trans); _needsMatrixUpdate = true; }
	void setRotation(glm::vec4 rotation) { _transform.setRotation(rotation); _needsMatrixUpdate = true; }
	void rotate(float angle, glm::vec3 axis) { _transform.rotate(angle, axis); _needsMatrixUpdate = true; }
	void setScale(glm::vec3 scale) { _transform.setScale(scale); _needsMatrixUpdate = true; }

	void flagForUpdate() { _needsMatrixUpdate = true; }

};

