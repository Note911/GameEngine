#include "OpenGLRenderer.h"
#include "LogManager.h"


OpenGLRenderer::OpenGLRenderer(Camera* camera)
{
	this->camera = camera;
}


OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::initOpenGL(int screenWidth, int screenHeight) {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Default to monitor res and borderless window, because reasons
	_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
		LogManager::getInstance().error("SDL Window could not be created!");

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr)
		LogManager::getInstance().error("GLContext could not be created!");

	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
		LogManager::getInstance().error("Glew did not initialize!");

	std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//Set VSYNC
	SDL_GL_SetSwapInterval(1);
}

void OpenGLRenderer::renderScene(SceneGraph* scene, float time) {
	_time = time;

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Render the scene
	RenderList::drawAllObjects(camera);

	//Swap the buffer	

	SDL_GL_SwapWindow(_window);
	camera->update();
}

void OpenGLRenderer::calculateFPS() {
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

float OpenGLRenderer::getFPS() {
	return _fps;
}