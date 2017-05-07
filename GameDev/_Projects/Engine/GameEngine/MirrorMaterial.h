#pragma once
#include "Material.h"
class MirrorMaterial : public Material {
public:
	MirrorMaterial(GLSLProgram* shader, GLTexture texture);
	~MirrorMaterial();

	GLTexture* skybox;

	void draw() {
		GLint textureLocation = _shaderProgram->getUniformLocation("posX");
		glUniform1i(textureLocation, 0);

		textureLocation = _shaderProgram->getUniformLocation("negX");
		glUniform1i(textureLocation, 1);

		textureLocation = _shaderProgram->getUniformLocation("posY");
		glUniform1i(textureLocation, 2);

		textureLocation = _shaderProgram->getUniformLocation("negY");
		glUniform1i(textureLocation, 3);

		textureLocation = _shaderProgram->getUniformLocation("posZ");
		glUniform1i(textureLocation, 4);

		textureLocation = _shaderProgram->getUniformLocation("negZ");
		glUniform1i(textureLocation, 5);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, skybox[0].id);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, skybox[1].id);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, skybox[2].id);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, skybox[3].id);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, skybox[4].id);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, skybox[5].id);

	};
};

