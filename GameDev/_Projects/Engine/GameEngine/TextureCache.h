#pragma once
#include <map>
#include "GLTexture.h"

class TextureCache {
public:
	//returns a handle of a specified texture
	GLTexture getTexture(std::string filePath);
	static TextureCache* getInstance() {
		if (_instance == nullptr)
			_instance = new TextureCache();
		return _instance;
	}
	~TextureCache();
private:
	TextureCache();

	static TextureCache* _instance;
	std::map<std::string, GLTexture> _textureMap;
};

