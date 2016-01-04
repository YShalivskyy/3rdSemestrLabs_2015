#pragma once
#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"

#define DEFAULT_PROGRAM "defaultProgram"
namespace Engine
{
	class CustomEngine
	{

	public:
		CustomEngine();
		~CustomEngine();

		//OpenGL and manager init
		bool init(int &argc, char** argv);
		bool init(int &argc, char** argv, int windowWidth, int windowHeight, int windowPositionX, int windowPositionY);
		//Loop
		void run();

		//Getters
		Managers::SceneManager*  getSceneManager()  const;
		Managers::ShaderManager* getShaderManager() const;
		Managers::ModelManager* getModelManager() const;

	private:
		Managers::SceneManager*  mSceneManager;
		Managers::ShaderManager* mShaderManager;
		Managers::ModelManager* mModelManager;

	};
}