#pragma once
#include <map>
#include "ShaderManager.h"
#include "../Rendering/GameObject.h"
#include "../Rendering/Models/Sphere.h"
#include "../Rendering/Models/Surface.h"


using namespace Engine::Rendering;
namespace Engine
{
	namespace Managers
	{
		class ModelManager
		{
		public:
			ModelManager();
			~ModelManager();

			void draw();
			void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			void update();
			void deleteModel(const std::string& gameModelName);
			const GameObject& getModel(const std::string& gameModelName) const;
			void setModel(std::string modelName, GameObject *model);
			void translateCamera(glm::vec3& vector);
			void rotateCamera(glm::vec3& vector);
			void launchObjects(glm::vec3& vector);
		private:
			std::map<std::string, GameObject*> gameModelList;
		};
	}
}