#include "MaterialCache.h"
#include <iostream>

MaterialCache* MaterialCache::_instance;

MaterialCache::MaterialCache()
{
	_materialMap = std::map<std::string, Material>();
}

MaterialCache::~MaterialCache()
{
	_materialMap.clear();
	_instance = nullptr;
}

Material* MaterialCache::getMaterial(std::string name) {
	//return an interator pointing to the image in the material map
	auto matMapIter = _materialMap.find(name);

	// if the iterator is actually in the map
	if (matMapIter == _materialMap.end()) {
		std::cout << "Material: " + name + " could not be found!\n";
		Material* newMaterial = new Material(*getMaterial("default"));
		return newMaterial;
	}
	std::cout << "Found Material: " + name + "\n";
	return new Material(matMapIter->second);
}
void MaterialCache::addMaterial(std::string name, Material material) {
	_materialMap.insert(make_pair(name, material));
}
