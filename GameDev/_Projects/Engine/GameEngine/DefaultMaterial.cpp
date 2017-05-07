#include "DefaultMaterial.h"



DefaultMaterial::DefaultMaterial(GLSLProgram* shader, GLTexture texture) : DefaultMaterial::Material(shader, texture) {

}


DefaultMaterial::~DefaultMaterial() {
	Material::~Material();
}

void DefaultMaterial::draw() {
	Material::draw();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _shaderProgram->getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

}
