#include "ModelManager.h"

using namespace Engine::Managers;
using namespace Engine::Rendering;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	for (auto model : gameModelList)
		delete model.second;
	gameModelList.clear();
}

void ModelManager::deleteModel(const std::string& gameModelName)
{
	GameObject* model = gameModelList[gameModelName];
	model->destroy();
	gameModelList.erase(gameModelName);
}

const GameObject& ModelManager::getModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelManager::setModel(std::string modelName, GameObject * model)
{
	gameModelList[modelName] = model;
}

void ModelManager::translateCamera(glm::vec3& vector)
{
	for (auto model : gameModelList)
		model.second->translateCamera(vector);
}

void ModelManager::rotateCamera(glm::vec3& vector)
{
	for (auto model : gameModelList)
		model.second->rotateCamera(vector);
}

void Engine::Managers::ModelManager::launchObjects(glm::vec3 & vector)
{
	for (auto model : gameModelList)
		model.second->launchObject(vector);
}

void ModelManager::update()
{
	for (auto model : gameModelList)
		model.second->update();
}

void ModelManager::draw()
{
	for (auto model : gameModelList)
		model.second->draw();
}

void ModelManager::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	for (auto model : gameModelList)
		model.second->draw(projectionMatrix, viewMatrix);
}