#pragma once
#include <string>
#include <glew.h>
#include <string>
class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	void use();

	void unuse();

	std::string name;
private:
	void compileShader(const std::string filePath, GLuint id);

	GLuint _programID;
	GLuint _numAttributes;
	GLuint _vertexShaderID, _fragmentShaderID;


};

