#pragma once
#include "AbstractRenderer.h"
#include <SDL.h>
#include <glew.h>
#include <vector>

#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "SceneGraph.h"
#include "LogManager.h"

class OpenGLRenderer : public AbstractRenderer
{
public:
	OpenGLRenderer(Camera* camera);
	~OpenGLRenderer();
	void initOpenGL(int screenWidth, int screenHeight);
	void renderScene(SceneGraph* scene, float time);
	void calculateFPS();
	float getFPS();

	void AbstractRenderer::renderPrimitive() {
	}
private:
	SDL_Window* _window;
	float _fps, _maxFps, _time, _frameTime;
};

