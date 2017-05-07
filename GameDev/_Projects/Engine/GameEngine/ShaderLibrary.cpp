#include "ShaderLibrary.h"
#include <iostream>
ShaderLibrary* ShaderLibrary::_instance;

ShaderLibrary::ShaderLibrary()
{
	_shaderMap = std::map<std::string, GLSLProgram*>();
}

ShaderLibrary::~ShaderLibrary()
{
	_shaderMap.clear();
	_instance = nullptr;
}

GLSLProgram* ShaderLibrary::getShader(std::string name) {
	//return an interator pointing to the image in the material map
	auto shaderMapIter = _shaderMap.find(name);

	// if the iterator is actually in the map
	if (shaderMapIter == _shaderMap.end()) {
		std::cout << "Shader: " + name + " could not be found!\n";
		return nullptr;
	}
	std::cout << "Found Shader: " + name + "\n";
	return shaderMapIter->second;
}
void ShaderLibrary::addShader(std::string name, GLSLProgram* shader) {
	_shaderMap.insert(make_pair(name, shader));
}