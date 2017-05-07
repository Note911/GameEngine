#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


TextureCache* TextureCache::_instance;

TextureCache::TextureCache()
{
	_textureMap = std::map<std::string, GLTexture>();
}

TextureCache::~TextureCache()
{
	_textureMap.clear();
	_instance = nullptr;
}

GLTexture TextureCache::getTexture(std::string filePath) {
	//return an interator pointing to the image in the texturemap
	auto texMapIter = _textureMap.find(filePath);

	// if the iterator is actually in the map
	if (texMapIter == _textureMap.end()) {
		//its not in there so make a new texture
		//load a new texture
		GLTexture newTexture = ImageLoader::loadPNG(filePath);
		//insert it into the map
		_textureMap.insert(make_pair(filePath, newTexture));

		std::cout << "Loaded new Texture!\n";
		return newTexture;
	}
	std::cout << "Loaded used Texture!\n";
	return texMapIter->second;
}
