#pragma once
#include <map>
#include "GLSLProgram.h"
class ShaderLibrary
{
public:
	static ShaderLibrary* _instance;

	static ShaderLibrary* getInstance() {
		if (_instance == nullptr)
			_instance = new ShaderLibrary();
		return _instance;
	}
	//returns a copy of a specified texture , textures are small so this is ok for now
	GLSLProgram* getShader(std::string name);
	void addShader(std::string name, GLSLProgram* shader);
	~ShaderLibrary();

private:
	ShaderLibrary();

	std::map<std::string, GLSLProgram*> _shaderMap;
};

