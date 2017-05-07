#pragma once
#include "TextureCache.h"
#include "MaterialCache.h"
#include "ShaderLibrary.h"

static class ResourceManager
{
	//change to singleton later
public:
	static GLTexture getTexture(std::string filePath);
	static GLSLProgram* getShader(std::string name);
	static Material* getMaterial(std::string name);

	static ResourceManager* getInstance() {
		if (_instance == nullptr)
			_instance = new ResourceManager();
		return _instance;
	}
	~ResourceManager();
private:
	ResourceManager();

	static ResourceManager* _instance;

	static TextureCache* _textureCache;
	static ShaderLibrary* _shaderLibrary;
	static MaterialCache* _materialCache;

};

