#include "MainGame.h"
#include <iostream>
#include <string>
#include "Randomizer.h"

const int NUM_ROWS = 50;
const int NUM_COLS = 50;

V_Randomizer *random;

bool mousePressed = false;


//Temp error function
void fatalError(std::string errorStr) {
	std::cout << errorStr << "\n";
	SDL_Quit();
}

MainGame::MainGame() {
	random = new V_Randomizer();

	_window = nullptr;
	_screenWidth = 768;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
	_frameRate = 250;
	_timeSinceLastFrame = 0;

	float tileWidth = _screenWidth / (float)NUM_ROWS;
	float tileHeight = _screenHeight / (float)NUM_COLS;

	std::cout << tileWidth << " " << tileHeight << "\n";

	int numTiles = NUM_ROWS * NUM_COLS;

	_tiles = new Tile**[NUM_ROWS];
	for (int i = 0; i < NUM_ROWS; ++i)
		_tiles[i] = new Tile*[NUM_COLS];

	bool aliveSwap = true;
	for (int x = 0; x < NUM_ROWS; ++x)
		for (int y = 0; y < NUM_COLS; ++y) {
			_tiles[x][y] = new Tile(Vec2(x * tileWidth, y * tileHeight), tileWidth, tileHeight, false);

		}
}

MainGame::~MainGame() {}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	//Init sdl
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	//Error check
	if (_window == nullptr)
		fatalError("Window did not initialize! \n");
	//Create the window context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	//Error check
	if (glContext == nullptr)
		fatalError("Gl Context did not initialize! \n");
	//Initialize glew

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		fatalError("Glew did not initalize correctly! \n");

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Set background color
	glClearColor(1,1,1,1.0);
}

void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT) {
		parseInput();
		drawScreen();
		if (_gameState == GameState::RUNNING) {
			_timeSinceLastFrame++;
			if (_timeSinceLastFrame >= _frameRate) {
				_timeSinceLastFrame = 0;
				for (int x = 0; x < NUM_ROWS; ++x) {
					for (int y = 0; y < NUM_COLS; ++y) {
						int c = checkTiles(x, y);
						//Check it the tile we are looking at is alive
						if (_tiles[x][y]->alive) {
							if (c < 2)
								_tiles[x][y]->kill = true;
							else if (c > 3)
								_tiles[x][y]->kill = true;
						}
						else
							if (c == 3)
								_tiles[x][y]->revive = true;
					}
				}
				for (int x = 0; x < NUM_ROWS; ++x)
					for (int y = 0; y < NUM_COLS; ++y) {
						_tiles[x][y]->killTile();
						_tiles[x][y]->reviveTile();
					}

			}
		}

	}
}

void MainGame::parseInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_MOUSEMOTION :
				//std::cout << evnt.motion.x << " " << evnt.motion.y << "\n";
				if (mousePressed) {
					for (int x = 0; x < NUM_ROWS; ++x) {
						for (int y = 0; y < NUM_COLS; ++y) {
							if (_tiles[x][y]->contains(evnt.motion.x, evnt.motion.y)) {
								_tiles[x][y]->alive = true;
							}
						}
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN :	
				for (int x = 0; x < NUM_ROWS; ++x) {
					for (int y = 0; y < NUM_COLS; ++y) {
						if (_tiles[x][y]->contains(evnt.motion.x, evnt.motion.y)) {
							_tiles[x][y]->alive = !_tiles[x][y]->alive;
						}
					}
				}
				mousePressed = true;
				break;
			case SDL_MOUSEBUTTONUP :
				mousePressed = false;
				break;
			case SDL_KEYDOWN : 
				if (evnt.key.keysym.sym == SDLK_SPACE)
					if (_gameState == GameState::PLAY)
						_gameState = GameState::RUNNING;
					else
						_gameState = GameState::PLAY;
				if (evnt.key.keysym.sym == SDLK_z)
					_frameRate += 10;
				if (evnt.key.keysym.sym == SDLK_x)
					_frameRate -= 10;
				break;
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::drawScreen() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	for (int x = 0; x < NUM_ROWS; ++x) {
		for (int y = 0; y < NUM_COLS; ++y) {
			if(_tiles[x][y]->alive || _tiles[x][y]->hasDied)
				_tiles[x][y]->drawTile(_screenWidth,_screenHeight);
		}
	}
	//Swap the buffer
	SDL_GL_SwapWindow(_window);
}

int MainGame::checkTiles(int x, int y) {
	//Counter to track how many neighbouring tiles are living
	int count = 0;
	//Check the top left most tile (x-1 , y-1)
	//make sure we stay in the index range
	if (x - 1 >= 0 && y - 1 >= 0)
		if (_tiles[x - 1][y - 1]->alive)
			count++;
	//Check the tile above (x, y-1)
	if (y - 1 >= 0)
		if (_tiles[x][y - 1]->alive)
			count++;
	//Check the top right most tile (x+1, y - 1)
	if(x +1 <= NUM_ROWS - 1 && y - 1 >= 0)
		if (_tiles[x + 1][y - 1]->alive)
			count++;
	//Check the left neighbour (x - 1, y)
	if (x - 1 >= 0)
		if (_tiles[x - 1][y]->alive)
			count++;
	//Check the right neighbour (x + 1, y)
	if(x + 1 <= NUM_ROWS - 1)
		if (_tiles[x + 1][y]->alive)
			count++;
	//Check the bottom left neighbour (x - 1, y + 1)
	if(x - 1 >= 0 && y + 1 <= NUM_COLS - 1)
		if (_tiles[x - 1][y + 1]->alive)
			count++;
	//Check the bottom  neighbour (x, y + 1)
	if (y + 1 <= NUM_COLS - 1)
		if (_tiles[x][y + 1]->alive)
			count++;
	//Check the bottom left neighbour (x + 1, y + 1)
	if (x + 1 <= NUM_ROWS - 1 && y + 1 <= NUM_COLS - 1)
		if (_tiles[x + 1][y + 1]->alive)
			count++;

	return count;
}