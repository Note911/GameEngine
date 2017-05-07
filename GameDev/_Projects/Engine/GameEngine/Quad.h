#pragma once
#include <glew.h>
#include <string>
#include <glm.hpp>
#include "gameObject.h"
#include "Vertex.h"

class Quad : public GameObject
{
public:
	Quad();
	~Quad();

	void virtual init(float width, float height, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	void virtual draw();
	void virtual update(glm::mat4 parentTransform);
	Vertex* getVertexdata() { return _vertexData; }
	
protected:

	float _width, _height;
private:
	Vertex* _vertexData;

	//Buffer ID
	GLuint _vboID;
};


