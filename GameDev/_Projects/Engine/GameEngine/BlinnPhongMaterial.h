#pragma once
#include "Material.h"

class BlinnPhongMaterial : public Material {
public:
	BlinnPhongMaterial(GLSLProgram* shader, GLTexture texture);
	~BlinnPhongMaterial();

	void draw() override;
};