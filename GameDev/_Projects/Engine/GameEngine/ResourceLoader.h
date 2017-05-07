#pragma once
#include "ResourceManager.h"

class ResourceLoader
{
private:
	static ResourceManager* _manager;
public:
	ResourceLoader();
	~ResourceLoader();

	void loadResources();
	void loadTextures();
	void loadShaders();
	void loadMaterials();
};

