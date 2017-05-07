#include "MainGame.h"
#include "LogManager.h"
#include "ImageLoader.h"
#include "ResourceLoader.h"

#include <iostream>
#include <string>

MainGame::MainGame() {
	_screenWidth = 1024;
	_screenHeight= 740;
	_maxFps = 60;
	_window = nullptr;
	_gameState = GameState::PLAY;

	_renderer = new OpenGLRenderer(&camera);
}

MainGame::~MainGame()
{
	_scene->clearScene();
	_renderer->~OpenGLRenderer();
	_scene->~SceneGraph();
}


void MainGame::run() {
	initSystems();

	//TEMPORARY:/
	Mesh* origin = new Mesh();
	origin->init(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0, 1.0f), "Cube");
	_scene->addToScene("Origin", (GameObject*)origin);

	testCube = new Mesh();
	testCube->init(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec3(1.5f, 1.5f, 1.5f), "Cube");
	//testCube->applyTexture("Textures/PlaceHolder/FFXIV.png");
	testCube->attachMaterial(ResourceManager::getMaterial("mirror"));
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "TestCube", (GameObject*)testCube);



	Sprite* bench1 = new Sprite();
	Sprite* bench2 = new Sprite();
	Sprite* bench3 = new Sprite();
	Sprite* bench4 = new Sprite();
	Sprite* bench5 = new Sprite();
	Sprite* bench6 = new Sprite();

	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	bench1->init(20.0f, 20.0f, glm::vec3(-10.0f, 0.0f, -0.0f), glm::vec4(0, 1, 0, 3.14/ 2.0), scale, "Textures/PlaceHolder/negX.png", "default");
	bench2->init(20.0f, 20.0f, glm::vec3(10.0f, 0.0f, -0.0f), glm::vec4(0, 1, 0, -3.14 / 2.0), scale, "Textures/PlaceHolder/posX.png", "default");
	bench3->init(20.0f, 20.0f, glm::vec3(0.0f, 10.0f, -0.0f), glm::vec4(1, 0, 0, 3.14 / 2.0), scale, "Textures/PlaceHolder/posY.png", "default");
	bench4->init(20.0f, 20.0f, glm::vec3(0.0f, -10.0f, -0.0f), glm::vec4(1, 0, 0, -3.14 / 2.0), scale, "Textures/PlaceHolder/negY.png", "default");
	bench5->init(20.0f, 20.0f, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec4(0, 1, 0, 3.14), scale, "Textures/PlaceHolder/negZ.png", "default");
	bench6->init(20.0f, 20.0f, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec4(0, 1, 0, 0), scale, "Textures/PlaceHolder/posZ.png", "default");

	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_1", bench1);
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_2", bench2);
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_3", bench3);
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_4", bench4);
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_5", bench5);
	_scene->addToSceneAsChildOf(_scene->getTree()->findNode("Origin"), "Bench_6", bench6);


	
	gameLoop();
}

void MainGame::initSystems() {
	_renderer->initOpenGL(_screenWidth, _screenHeight);
	ResourceLoader loader = ResourceLoader();
	loader.loadResources();
	_scene = new SceneGraph("RootNode", new GameObject());
	//Load the resources first 
	//initShaders();
}
void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_colorProgram.addAttribute("vertexPos");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();

	//_colorProgram.compileShaders("Shaders/phongShader.vert", "Shaders/phongShader.frag");
	//_colorProgram.addAttribute("inputPosition");
	//_colorProgram.addAttribute("inputTextureCoordinates");
	//_colorProgram.addAttribute("inputNormal");
	//_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks();

		_time = SDL_GetTicks() / 1000.0f;

		parseInput();
		calculateFPS();
		update();
		drawGame();

		//print every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			//std::cout << _fps << std::endl;
			frameCounter = 0;
		}
		float frameTicks = SDL_GetTicks() - startTicks;

		//cap fps at 60
		if (1000.0f / _maxFps > frameTicks) 
			SDL_Delay(1000.0f / _maxFps - frameTicks);

		//rotate the quads for testing
		//_scene->find("Bench_1")->rotate(0.01, glm::vec3(0.0f, 1.0f, 0.0f));
		//_scene->find("Bench_2")->rotate(0.01, glm::vec3(0.0f, 1.0f, 0.0f));
		//_scene->find("Bench_3")->rotate(0.01, glm::vec3(1.0f, 0.0f, 0.0f));
		//_scene->find("Bench_4")->rotate(0.01, glm::vec3(1.0f, 1.0f, 1.0f));
		//_scene->find("Bench_5")->rotate(0.01, glm::vec3(1.0f, 0.0f, 1.0f));
		//_scene->find("Bench_6")->rotate(0.01, glm::vec3(1.0f, 1.0f, 0.0f));
		//_scene->find("Bench_7")->rotate(0.01, glm::vec3(0.0f, 1.0f, 1.0f));
		//_scene->find("Bench_8")->rotate(0.01, glm::vec3(0.0f, 0.0f, 1.0f));
		//_scene->find("Bench_9")->rotate(0.01, glm::vec3(1.0f, 0.0f, 0.0f));

		_scene->find("TestCube")->rotate(0.01, glm::vec3(0.1f, 1.0f, 0.5f));
	}
}

void MainGame::parseInput() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt)){
		switch (evt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//std::cout << evt.motion.x << " " << evt.motion.y << "\n";
			//Camera* camera = _renderer->getCamera();
			//Transform cameraTransform = camera->getTransform();
			glm::vec2 mouseMotion = glm::vec2(evt.motion.x, evt.motion.y);
			float motionMag = sqrt(pow(mouseMotion.x, 2) + pow(mouseMotion.y, 2));
			mouseMotion /= motionMag; //normalizing

			if(motionMag > 0)
				_scene->find("Origin")->rotate(0.01f, glm::vec3(-mouseMotion.y, mouseMotion.x, 0.0f));
			//camera->setTransform(cameraTransform);
			break;
		}
	}
}

void MainGame::update() {
	_scene->updateScene();
	_scene->createRenderList();
}

void MainGame::drawGame() {
	_renderer->renderScene(_scene, _time);
}

void MainGame::calculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;

	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;
}