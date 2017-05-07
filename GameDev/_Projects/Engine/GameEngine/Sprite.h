#pragma once
#include <glew.h>
#include "GLTexture.h"
#include <string>
#include <glm.hpp>
#include "Quad.h"

class Sprite : public Quad
{
public:
	Sprite();
	~Sprite();

	void virtual init(float width, float height, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, std::string texturePath, std::string material);
	void virtual draw();
	void virtual update(glm::mat4 parentTransform);
};

