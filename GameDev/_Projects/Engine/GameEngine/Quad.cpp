#include "Quad.h"
#include <gtx/transform.hpp>




Quad::Quad()
{
	_vboID = 0;
}


Quad::~Quad()
{
	//Delete the buffer if it exists
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);


}

void Quad::init(float width, float height, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale) {
	_width = width;
	_height = height;
	
	//Set up transform matrix
	//create an identity matrix for the object
	GameObject::init(position, rotation, scale);

	//record the transform matrix by combining the translation, rotation and scale
	_transform.updateTransform(glm::mat4(1.0f));
	glm::mat4 transformMatrix = _transform.getTransform();


	//Generate the buffer ID if it hasnt already been created
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	_vertexData = new Vertex[6];
	for (int i = 0; i < 6; i++)
		_vertexData[i] = Vertex();

	//Top Left
	_vertexData[0].setPosition(glm::vec3(0.0f - _width / 2, 0.0f + _height / 2, 0.0f));
	_vertexData[0].setUV(0.0f, 1.0f);
	//Bottom Left:->value equal to bottom right, z value equal to top left)
	_vertexData[1].setPosition(glm::vec3(0.0f - _width / 2, 0.0f - _height / 2, 0.0f));
	_vertexData[1].setUV(0.0f, 0.0f);
	//Bottom Right.connect Triangle from bottom Left to top Right, therefore this vertex is equal to bottom right exept the y value
	_vertexData[2].setPosition(glm::vec3(0.0f + _width /2, 0.0f - _height / 2, 0.0f));
	_vertexData[2].setUV(1.0f, 0.0f);
	//top Left	  .
	_vertexData[3].setPosition(glm::vec3(0.0f - _width / 2, 0.0f + _height / 2, 0.0f));
	_vertexData[3].setUV(0.0f, 1.0f);
	//Top Right	  .
	_vertexData[4].setPosition(glm::vec3(0.0f + _width / 2, 0.0f + _height / 2, 0.0f));
	_vertexData[4].setUV(1.0f, 1.0f);
	//Bottom Right.
	_vertexData[5].setPosition(glm::vec3(0.0f + _width / 2, 0.0f - _height / 2, 0.0f));
	_vertexData[5].setUV(1.0f, 0.0f);


	Vertex tmpData[6];
	for (int i = 0; i < 6; i++) {
		glm::vec4 vertex = glm::vec4(_vertexData[i].position.x, _vertexData[i].position.y, _vertexData[i].position.z, 1.0f);
		vertex = transformMatrix * vertex;
		_vertexData[i].position = glm::vec3(vertex.x, vertex.y, vertex.z);
		tmpData[i] = _vertexData[i];
	}

	//Bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Upload vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(tmpData), tmpData, GL_STATIC_DRAW);

	//Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Quad::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	GameObject::draw();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::update(glm::mat4 parentTransform){
	if (needsUpdate()) {
		glm::mat4 inverseMatrix = _transform.getInverse();
		_transform.updateTransform(parentTransform);
		glm::mat4 transformMatrix = _transform.getTransform();
		
		Vertex tmpData[6];
		for (int i = 0; i < 6; i++) {
			glm::vec4 vertex = glm::vec4(_vertexData[i].position.x, _vertexData[i].position.y, _vertexData[i].position.z, 1.0f);
			vertex = inverseMatrix * vertex;
			vertex = transformMatrix * vertex;
			_vertexData[i].position = glm::vec3(vertex.x, vertex.y, vertex.z);
			tmpData[i] = _vertexData[i];
		}
		//recalculate the normals
		//since this is a plane already we can calculate the normal for only the first triangle and set them all equal
		glm::vec3 sideAB = tmpData[1].position - tmpData[0].position;
		glm::vec3 sideAC = tmpData[2].position - tmpData[0].position;
		glm::vec3 normal = glm::normalize(glm::cross(sideAB, sideAC));
		for (int i = 0; i < 6; i++)
			tmpData[i].setNormal(normal);

		//Bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Upload vertex data to the buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(tmpData), tmpData, GL_STATIC_DRAW);

		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	GameObject::update(parentTransform);
}


