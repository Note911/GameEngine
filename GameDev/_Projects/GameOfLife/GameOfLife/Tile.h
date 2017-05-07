#pragma once
#include "MathLib/Vec2.h"
#include <glew.h>
class Tile
{
public:
	Tile(Vec2 pos, float width, float height, bool alive);
	~Tile();
	bool alive;
	bool kill = false;
	bool revive = false;
	bool hasDied = false;
	Vec2 getPosition();
	Vec2 getDimentions();
	void drawTile(int screenWidth, int screenHeight);
	bool contains(float x, float y);
	void killTile();
	void reviveTile();
private:
	Vec2 _pos;
	float _width;
	float _height;
};

