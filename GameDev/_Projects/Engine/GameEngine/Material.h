#pragma once
#include "GLTexture.h"
#include "GLSLProgram.h"

class Material
{
protected:
	GLSLProgram* _shaderProgram;
	GLTexture _textureImage;

public:
	Material(GLSLProgram* shader, GLTexture texture);
	~Material();

	virtual void draw() {
		if (_textureImage.id != NULL)
			glBindTexture(GL_TEXTURE_2D, _textureImage.id);
	};

	GLSLProgram* getShaderProgram() { return _shaderProgram; }
	GLTexture getTextureImage() { return _textureImage; }
	void setTextureImage(GLTexture image) {
		_textureImage = image;
	}

private:
	void init(GLSLProgram* shader, GLTexture texture);


};

