#include "MirrorMaterial.h"
#include "ResourceManager.h"

MirrorMaterial::MirrorMaterial(GLSLProgram* shader, GLTexture texture) : Material(shader, texture) {
	skybox = new GLTexture[6];

	skybox[0] = ResourceManager::getTexture("Textures/PlaceHolder/posX.png");
	skybox[1] = ResourceManager::getTexture("Textures/PlaceHolder/negX.png");
	skybox[2] = ResourceManager::getTexture("Textures/PlaceHolder/posY.png");
	skybox[3] = ResourceManager::getTexture("Textures/PlaceHolder/negY.png");
	skybox[4] = ResourceManager::getTexture("Textures/PlaceHolder/posZ.png");
	skybox[5] = ResourceManager::getTexture("Textures/PlaceHolder/negZ.png");
}

MirrorMaterial::~MirrorMaterial() {
	Material::~Material();
}

