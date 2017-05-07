#include "ResourceManager.h"

TextureCache* ResourceManager::_textureCache;
ShaderLibrary* ResourceManager::_shaderLibrary;
MaterialCache* ResourceManager::_materialCache;

ResourceManager* ResourceManager::_instance;


ResourceManager::ResourceManager() {
	_textureCache = TextureCache::getInstance();
	_shaderLibrary = ShaderLibrary::getInstance();
	_materialCache = MaterialCache::getInstance();
}

ResourceManager::~ResourceManager() {
	_textureCache->~TextureCache();
	_shaderLibrary->~ShaderLibrary();
	_materialCache->~MaterialCache();
	_instance == NULL;
}

GLTexture ResourceManager::getTexture(std::string filePath) {
	return _textureCache->getTexture(filePath);
}

GLSLProgram* ResourceManager::getShader(std::string name) {
	return _shaderLibrary->getShader(name);
}

Material* ResourceManager::getMaterial(std::string name) {
	return _materialCache->getMaterial(name);
}