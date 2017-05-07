#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>



Sprite::Sprite() {

}


Sprite::~Sprite() {
	Quad::~Quad();
}


void Sprite::init(float width, float height, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, std::string texturePath, std::string material)  {
	Quad::init(width, height, position, rotation, scale);
	_texture = ResourceManager::getInstance()->getTexture(texturePath);
	if (material != "") {
		_material = ResourceManager::getInstance()->getMaterial(material);
		_material->setTextureImage(_texture);
	}
}


void Sprite::draw() {
	if(_texture.id != NULL)
		glBindTexture(GL_TEXTURE_2D, _texture.id);
	Quad::draw();
}

void Sprite::update(glm::mat4 parentTransform) {
	Quad::update(parentTransform);
}
