#pragma once

#include <Windows.h>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include "Tile.h"



enum class GameState {PLAY, RUNNING, EXIT};

class MainGame {
public:
	MainGame();
	~MainGame();

	void run();
private:
	void initSystems();
	void gameLoop();
	void parseInput();
	void drawScreen();
	int checkTiles(int x, int y);
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	Tile*** _tiles;
	int _frameRate;
	int _timeSinceLastFrame;
};

