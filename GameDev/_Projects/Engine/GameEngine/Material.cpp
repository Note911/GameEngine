#include "Material.h"



Material::Material(GLSLProgram* shader, GLTexture texture)
{
	init(shader, texture);
}

Material::~Material()
{
}


void Material::init(GLSLProgram* shader, GLTexture texture) {
	_shaderProgram = shader;
	_textureImage = texture;
}

