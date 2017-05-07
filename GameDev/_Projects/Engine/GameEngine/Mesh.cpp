#include "Mesh.h"
#include "Quad.h"
#include "ResourceManager.h"


Mesh::Mesh()
{
	_vboID = 0;
}


Mesh::~Mesh()
{
	//Delete the buffer if it exists
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Mesh::init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, std::string shapeName) {
	GameObject::init(position, rotation, scale);
	//Generate the buffer ID if it hasnt already been created
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	//CUBE..
	generateCube(scale, _vertexData);
	_numVerticies = 36;
	Vertex tmpData[36];
	for (int i = 0; i < 36; i++)
		tmpData[i] = _vertexData[i];

	//Bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Upload vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(tmpData), tmpData, GL_STATIC_DRAW);

	//Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::init(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, Vertex vertexData[]) {
	GameObject::init(position, rotation, scale);
	//Generate the buffer ID if it hasnt already been created
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	//Bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Upload vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::applyTexture(std::string texturePath) {
	 _texture = ResourceManager::getInstance()->getTexture(texturePath);
}

void Mesh::draw() {
	if(_texture.id != NULL)
		glBindTexture(GL_TEXTURE_2D, _texture.id);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	GameObject::draw();

	glDrawArrays(GL_TRIANGLES, 0, _numVerticies);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::update(glm::mat4 parentTransform) {
	if (needsUpdate()) {
		glm::mat4 inverseMatrix = _transform.getInverse();
		_transform.updateTransform(parentTransform);
		glm::mat4 transformMatrix = _transform.getTransform();

		Vertex tmpData[36];
		for (int i = 0; i < 36; i++) {
			glm::vec4 vertex = glm::vec4(_vertexData[i].position.x, _vertexData[i].position.y, _vertexData[i].position.z, 1.0f);
			glm::vec4 normal = glm::vec4(_vertexData[i].normal.x, _vertexData[i].normal.y, _vertexData[i].normal.z, 1.0f);
			vertex = inverseMatrix * vertex;
			normal = glm::normalize(vertex);
			vertex = transformMatrix * vertex;
			_vertexData[i].position = glm::vec3(vertex.x, vertex.y, vertex.z);
			_vertexData[i].setNormal(glm::vec3(normal.x, normal.y, normal.z));
			tmpData[i] = _vertexData[i];
		}

		//Bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Upload vertex data to the buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(tmpData), tmpData, GL_STATIC_DRAW);

		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	GameObject::update(parentTransform);
}

void Mesh::generateCube(glm::vec3 dimentions, Vertex* &vertexData) {
	
	vertexData = new Vertex[36];
	for (int i = 0; i < sizeof(vertexData); i++)
		vertexData[i] = Vertex();

	Quad sides[6];

 	//loop 6 times creating 6 quads
	for (int i = 0; i < 6; i++)
		sides[i] = Quad();

	sides[0].init(dimentions.x, dimentions.y, glm::vec3(_position.x, _position.y, _position.z + (dimentions.z / 2)), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	sides[1].init(dimentions.x, dimentions.y, glm::vec3(_position.x + (dimentions.x / 2), _position.y, _position.z), glm::vec4(0.0f, 1.0f, 0.0f, -1.5708f), glm::vec3(1.0f, 1.0f, 1.0f));
	sides[2].init(dimentions.x, dimentions.y, glm::vec3(_position.x, _position.y, _position.z - (dimentions.z / 2)), glm::vec4(0.0f, 1.0f, 0.0f, -3.14159f), glm::vec3(1.0f, 1.0f, 1.0f));
	sides[3].init(dimentions.x, dimentions.y, glm::vec3(_position.x - (dimentions.x / 2), _position.y, _position.z), glm::vec4(0.0f, 1.0f, 0.0f, -4.71239), glm::vec3(1.0f, 1.0f, 1.0f));
	sides[4].init(dimentions.x, dimentions.y, glm::vec3(_position.x, _position.y + (dimentions.y / 2), _position.z), glm::vec4(1.0f, 0.0f, 0.0f, -1.5708f), glm::vec3(1.0f, 1.0f, 1.0f));
	sides[5].init(dimentions.x, dimentions.y, glm::vec3(_position.x, _position.y - (dimentions.y / 2), _position.z), glm::vec4(1.0f, 0.0f, 0.0f, 1.5708f), glm::vec3(1.0f, 1.0f, 1.0f));

	/*(0,0,0), (1,-1,0)
	(1,0,0), (1,-1,-1)
	(1,0,-1),(0,-1,-1)
	(0,0,-1),(0,-1,0)
	(0,0,-1),(1,0,0)
	(0,-1,0),(1,-1,-1)*/


	for (int i = 0; i < 6; i++) {
		Vertex* sideVertexData = sides[i].getVertexdata();
		vertexData[0 + i * 6].setPosition(sideVertexData[0].position);
		vertexData[0 + i * 6].setUV(sideVertexData[0].uv);
		vertexData[0 + i * 6].setColor(sideVertexData[0].color);
		vertexData[0 + i * 6].setNormal(glm::normalize(sideVertexData[0].position));
					 
		vertexData[1 + i * 6].setPosition(sideVertexData[1].position);
		vertexData[1 + i * 6].setUV(sideVertexData[1].uv);
		vertexData[1 + i * 6].setColor(sideVertexData[1].color);
		vertexData[1 + i * 6].setNormal(glm::normalize(sideVertexData[1].position));
					 
		vertexData[2 + i * 6].setPosition(sideVertexData[2].position);
		vertexData[2 + i * 6].setUV(sideVertexData[2].uv);
		vertexData[2 + i * 6].setColor(sideVertexData[2].color);
		vertexData[2 + i * 6].setNormal(glm::normalize(sideVertexData[2].position));
					 
		vertexData[3 + i * 6].setPosition(sideVertexData[3].position);
		vertexData[3 + i * 6].setUV(sideVertexData[3].uv);
		vertexData[3 + i * 6].setColor(sideVertexData[3].color);
		vertexData[3 + i * 6].setNormal(glm::normalize(sideVertexData[3].position));
					 
		vertexData[4 + i * 6].setPosition(sideVertexData[4].position);
		vertexData[4 + i * 6].setUV(sideVertexData[4].uv);
		vertexData[4 + i * 6].setColor(sideVertexData[4].color);
		vertexData[4 + i * 6].setNormal(glm::normalize(sideVertexData[4].position));
					 
		vertexData[5 + i * 6].setPosition(sideVertexData[5].position);
		vertexData[5 + i * 6].setUV(sideVertexData[5].uv);
		vertexData[5 + i * 6].setColor(sideVertexData[5].color);
		vertexData[5 + i * 6].setNormal(glm::normalize(sideVertexData[5].position));
	}
}