#pragma once
#include "Material.h"
class DefaultMaterial : public Material {
public:
	DefaultMaterial(GLSLProgram* shader, GLTexture texture);
	~DefaultMaterial();

	void draw() override;
};

