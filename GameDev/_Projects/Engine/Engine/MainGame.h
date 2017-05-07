#pragma once
#include "OpenGLRenderer.h"
#include "Mesh.h"


enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void parseInput();
	void drawGame();
	void update();
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth, _screenHeight;
	GameState _gameState;

	GLSLProgram _colorProgram;
	OpenGLRenderer* _renderer;
	SceneGraph* _scene;
	Camera camera;

	//Test//
	Mesh* testCube;

	float _time;
	float _fps;
	float _maxFps;
	float _frameTime;
};

