#ifndef ABSTRACT_RENDERER_H
#define ABSTRACT_RENDERER_H
#pragma once
#include <glm.hpp>
#include "SceneGraph.h"
#include "Camera.h"
//This is an interface to define perameters for a renderer class.
//The class contains a reference to a scene graph (also make this class) which contains a list of all renderable objects which have been regestered too the scene.
   

class AbstractRenderer {
protected:
	virtual void renderPrimitive() = 0;
	Camera* camera;
	bool wireFrameMode = false;
	glm::vec3 renderColor;

public:
	AbstractRenderer() : renderColor(glm::vec3(1.0f, 1.0f, 1.0f)) {}
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setWireFrameMode(bool enable);
	bool isWireFrameEnabled();
	Camera* getCamera() { return camera; }
	
};
#endif 