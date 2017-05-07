#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL.h>
#include "Transform.h"
class Camera
{
public:
	Camera();
	~Camera();

	void init(int screenWidth, int screenHeight);
	
	void update();

	//Setters
	void setTransform(Transform& position) {
		_transform = position; _needsMatrixUpdate = true;
	}
	void setScale(float scale) { _scale = scale;  }
	//Gettesrs
	Transform getTransform() { return _transform; }
	float getScale() { return _scale; }
	glm::mat4 getProjectionMatrix() { return _projectionMatrix; }

private:
	int _screenHeight, _screenWidth;
	bool _needsMatrixUpdate;
	Transform _transform;
	float _scale;
	glm::mat4 _projectionMatrix;

};

