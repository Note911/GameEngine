#pragma once
#include <glm.hpp>
#include <gtx/transform.hpp>

struct Transform {
public:
	//getters
	glm::vec3 getPosition() { return _position; }
	glm::vec4 getRotation() { return _rotation; }
	glm::vec3 getScale() { return _scale; }

	glm::mat4 getTransform() {
		return _transform;
	}

	glm::mat4 getInverse() {
		return _inverse;
	}

	glm::mat4 getNormal() {
		return _normal;
	}

	void updateTransform(glm::mat4 parentMatrix) {
		//Identity Matrix
		glm::mat4 _identity = glm::mat4(1.0f);
		//Translation Matrix
		glm::mat4 traslationMatrix = glm::translate(_position);
		//Rotation Matrix
		glm::mat4 rotationMatrix = glm::rotate(_rotation.w, glm::vec3(_rotation.x, _rotation.y, _rotation.z));
		//Scaling Matrix
		glm::mat4 scalingMatrix = glm::scale(_scale);

		_transform = _identity * traslationMatrix * rotationMatrix * scalingMatrix;
		_transform = parentMatrix * _transform;
		_inverse = glm::inverse(_transform);
		_normal = glm::inverse(glm::transpose(_transform));
	}

	//setters
	void setPosition(glm::vec3 position) { _position = position; }
	void translate(glm::vec3 trans) { _position += trans; }
	void setRotation(glm::vec4 rotation) { _rotation = rotation; }
	void rotate(float angle, glm::vec3 axis) { _rotation = glm::vec4(axis.x, axis.y, axis.z, _rotation.w + angle); }
	void setScale(glm::vec3 scale) { _scale = scale; }

protected:
	glm::vec3 _position;
	glm::vec4 _rotation;
	glm::vec3 _scale;
	glm::mat4 _inverse;
	glm::mat4 _normal;
	glm::mat4 _transform;
};
