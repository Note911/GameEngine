#pragma once
#include <glew.h>
#include <glm.hpp>


struct Vertex {

	glm::vec3 position;

	struct Color {
		GLubyte r, g, b, a;
	};

	Color color;
	glm::vec2 uv;
	glm::vec3 normal;


	void setPosition(glm::vec3 position) {
		this->position = glm::vec3(position.x, position.y, position.z);
	}

	void setColor(Color color) {
		this->color = color;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(glm::vec2 uv) {
		this->uv = glm::vec2(uv.x, uv.y);
	}

	void setUV(float u, float v) {
		uv.x = u;
		uv.y = v;
	}

	void setNormal(glm::vec3 normal) {
		this->normal = glm::normalize(normal);
	}
};