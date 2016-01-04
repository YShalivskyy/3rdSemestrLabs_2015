#include "CustomEngine.h"
using namespace Engine;
using namespace Core;

#define DEFAULT_MINOR_OPENGL_VERSION 3
#define DEFAULT_MAJOR_OPENGL_VERSION 4
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_POSITION_X 100
#define DEFAULT_WINDOW_POSITION_Y 90

CustomEngine::CustomEngine()
{

}

bool CustomEngine::init(int &argc, char** argv)
{
	return init(argc, argv, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_POSITION_X, DEFAULT_WINDOW_POSITION_Y);
}

bool CustomEngine::init(int &argc, char** argv, int windowWidth, int windowHeight, int windowPositionX, int windowPositionY)
{
	WindowInfo window(std::string("OpenGL Window"),
		windowPositionX, windowPositionY,
		windowWidth, windowHeight, true);
	ContextInfo context(DEFAULT_MAJOR_OPENGL_VERSION, DEFAULT_MINOR_OPENGL_VERSION, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);

	Init::InitGlut::init(argc, argv, window, context, frameBufferInfo);

	mSceneManager = new Managers::SceneManager();

	Core::Init::InitGlut::setListener(mSceneManager);


	mShaderManager = new Managers::ShaderManager();
	mShaderManager->createProgram(DEFAULT_PROGRAM,
		"Shaders\\DumbbellVertexShader.glsl",
		"Shaders\\DumbbellFragmentShader.glsl");


	if (mSceneManager && mShaderManager)
	{
		mModelManager = new Managers::ModelManager();
		mSceneManager->setModelManager(mModelManager);
	}
	else
		return false;

	return true;
}
//Create the loop
void CustomEngine::run()
{
	Init::InitGlut::run();
}

Managers::SceneManager* CustomEngine::getSceneManager() const
{
	return mSceneManager;
}

Managers::ShaderManager* CustomEngine::getShaderManager() const
{
	return mShaderManager;
}

Managers::ModelManager* CustomEngine::getModelManager() const
{
	return mModelManager;
}



CustomEngine::~CustomEngine()
{
	if (mSceneManager)
		delete mSceneManager;

	if (mShaderManager)
		delete mShaderManager;

	if (mModelManager)
		delete mModelManager;

}