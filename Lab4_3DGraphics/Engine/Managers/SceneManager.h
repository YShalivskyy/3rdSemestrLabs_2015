#pragma once
#include "ShaderManager.h"
#include "ModelManager.h"
#include "../Core/Init/EventListener.h"
namespace Engine
{
	namespace Managers
	{
		class SceneManager : public Engine::Core::EventListener
		{
		public:
			SceneManager();
			~SceneManager();

			void setModelManager(Managers::ModelManager*& modelManager);

			virtual void notifyBeginFrame();
			virtual void notifyDisplayFrame();
			virtual void notifyEndFrame();
			virtual void notifyReshape(int width,
				int height,
				int previousWidth,
				int previousHeight);
			virtual void notifyTranslation(float, float, float);
			virtual void notifyRotation(float, float, float);
			virtual void notifyLaunch(float, float, float);


		private:
			glm::mat4 lookAt(glm::vec3& position,
				glm::vec3& target,
				glm::vec3& up);
			glm::mat4 getPerspective(float width, float height, float n, float f, float angle);
			Engine::Managers::ShaderManager* shaderManager;
			Engine::Managers::ModelManager* modelManager;
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			//Camera atributes
			glm::vec3 position, target, up;

			void refreshCamera();
			
		};
	}
}