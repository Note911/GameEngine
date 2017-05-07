#pragma once
#include <map>
#include "Material.h"
class MaterialCache {
public:
	static MaterialCache* _instance;

	static MaterialCache* getInstance() {
		if (_instance == nullptr)
			_instance = new MaterialCache();
		return _instance;
	}
	//returns a copy of a specified material.  It must be a copy because materials may have different uniforms on a per object basis
	Material* getMaterial(std::string name);
	void addMaterial(std::string name, Material material);
	~MaterialCache();

private:
	MaterialCache();

	std::map<std::string, Material> _materialMap;
};



