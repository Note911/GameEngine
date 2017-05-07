#include "BlinnPhongMaterial.h"

BlinnPhongMaterial::BlinnPhongMaterial(GLSLProgram* shader, GLTexture texture) : Material(shader, texture) {}

BlinnPhongMaterial::~BlinnPhongMaterial() {
	Material::~Material();
}

void BlinnPhongMaterial::draw() {
	Material::draw();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _shaderProgram->getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
}