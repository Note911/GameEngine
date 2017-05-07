#include "ResourceLoader.h"
#include "ImageLoader.h"
#include "BlinnPhongMaterial.h"
#include "MirrorMaterial.h"

ResourceManager* ResourceLoader::_manager = nullptr;

ResourceLoader::ResourceLoader() {
	_manager = ResourceManager::getInstance();
}

ResourceLoader::~ResourceLoader() {}

void ResourceLoader::loadResources() {
	//Default Texture
//	GLTexture defaultTexture = GLTexture();
	GLTexture defaultTexture = _manager->getTexture("Textures/PlaceHolder/Default.png");
	//Default Shader
	GLSLProgram* defaultShader = new GLSLProgram();
	defaultShader->compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	defaultShader->addAttribute("vertexPos");
	defaultShader->addAttribute("vertexColor");
	defaultShader->addAttribute("vertexUV");
	//defaultShader->addAttribute("inputNormal");
	defaultShader->linkShaders();
	ShaderLibrary::getInstance()->addShader("default", defaultShader);

	GLSLProgram* mirrorShader = new GLSLProgram();
	mirrorShader->compileShaders("Shaders/mirrorShader.vert", "Shaders/mirrorShader.frag");
	mirrorShader->addAttribute("vertexPos");
	mirrorShader->addAttribute("vertexColor");
	mirrorShader->addAttribute("vertexUV");
	mirrorShader->addAttribute("inputNormal");
	mirrorShader->linkShaders();
	ShaderLibrary::getInstance()->addShader("mirror", mirrorShader);
	//Default Material
	BlinnPhongMaterial defaultMaterial = BlinnPhongMaterial(defaultShader, defaultTexture);
	MaterialCache::getInstance()->addMaterial("default", defaultMaterial);
	MirrorMaterial mirrorMaterial = MirrorMaterial(mirrorShader, defaultTexture);
	MaterialCache::getInstance()->addMaterial("mirror", mirrorMaterial);


}

void ResourceLoader::loadTextures(){}

void ResourceLoader::loadShaders(){}

void ResourceLoader::loadMaterials(){}