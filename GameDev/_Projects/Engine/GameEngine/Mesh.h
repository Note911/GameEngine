#pragma once
#include "Vertex.h"
#include "GLTexture.h"
#include <string>
#include "GameObject.h"

class Mesh : public GameObject{
public:
	Mesh();
	~Mesh();

	void setPosition(glm::vec3 position) { _position = position; }
	glm::vec3 getPosition() { return _position; }

	Vertex* getVertexData() { return _vertexData; }

	void virtual init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, std::string shapeName);
	void virtual init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, Vertex vertexData[]);
	void virtual applyTexture(std::string texturePath);
	void virtual update(glm::mat4 parentTransform);
	void virtual draw();

protected:
	glm::vec3 _position;


private:
	int _numVerticies = 0;
	Vertex* _vertexData;
	//Buffer ID
	GLuint _vboID;
	//Texture
	GLTexture _texture;
	//Preset shapes
	void generateCube(glm::vec3 dimentions, Vertex* &vertexData);
};

