#include "Tile.h"
#include <iostream>



Tile::Tile(Vec2 pos, float width, float height, bool alive){
	_pos = pos;
	_width = width;
	_height = height;
	this->alive = alive;
}


Tile::~Tile(){
}

Vec2 Tile::getPosition() {
	return _pos;
}

Vec2 Tile::getDimentions() {
	return Vec2(_width, _height);
}

void Tile::drawTile(int screenWidth, int screenHeight) {
	float x1 = -1 + (_pos.x) / (screenWidth / 2);
	float y1 = 1 - (_pos.y) / (screenHeight / 2);
	float x2 = (x1 + (_width / (screenWidth / 2)));
	float y2 = (y1 - (_height / (screenHeight / 2)));
	if(alive)
		glColor3f(0.0f, 0.0f, 0.0f);
	else if(hasDied)
		glColor3f(0.0f, 1.0f, 0.0f);
	else//not really needed
		glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		//Top left
		glVertex2f(x1, y1);
		//Top right
		glVertex2f(x2, y1);
		//Bottom right
		glVertex2f(x2, y2);
		//Bottom left
		glVertex2f(x1 ,y2);
	glEnd();
}

bool Tile::contains(float x, float y) {
	if (x >= _pos.x  && x <= _pos.x  + _width)
		if (y >= _pos.y && y <= _pos.y + _height)
			return true;
		else
			return false;
	else
		return false;
}

void Tile::killTile() {
	if (alive && kill) {
		kill = false;
		alive = false;
		hasDied = true;
	}
}

void Tile::reviveTile() {
	if (!alive && revive) {
		revive = false;
		alive = true;
	}
}
