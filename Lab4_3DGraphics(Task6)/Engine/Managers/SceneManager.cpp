#include "SceneManager.h"

Engine::Managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	projectionMatrix = getPerspective((float)glutGet(GLUT_WINDOW_WIDTH),
		(float)glutGet(GLUT_WINDOW_HEIGHT),
		0.1f, 2000.0f, 45);
	position = glm::vec3(-0.001, 0, 0.001);
	target = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
	refreshCamera();
}

Engine::Managers::SceneManager::~SceneManager()
{
}

void Engine::Managers::SceneManager::setModelManager(Managers::ModelManager *& modelManager)
{
	this->modelManager = modelManager;
}

void Engine::Managers::SceneManager::notifyBeginFrame()
{
	modelManager->update();
}

void Engine::Managers::SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	modelManager->draw();
	modelManager->draw(projectionMatrix, viewMatrix);
}

void Engine::Managers::SceneManager::notifyEndFrame()
{
}

void Engine::Managers::SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight)
{
}

void Engine::Managers::SceneManager::notifyTranslation(float x, float y, float z)
{
	modelManager->translateCamera(glm::vec3(x, y, z));
	//refreshCamera();
}

void Engine::Managers::SceneManager::notifyRotation(float x, float y, float z)
{
	modelManager->rotateCamera(glm::vec3(x * M_PI / 180, y * M_PI / 180, z * M_PI / 180));

}

void Engine::Managers::SceneManager::notifyLaunch(float x, float y, float z)
{
	modelManager->launchObjects(glm::vec3(x, y, z));
}

glm::mat4 Engine::Managers::SceneManager::lookAt(glm::vec3 & position, glm::vec3 & target, glm::vec3 & up)
{
	glm::vec3 f = position - target;
	f = glm::normalize(f);
	glm::vec3 s = glm::cross(f, up);
	s = glm::normalize(s);
	glm::vec3 v = glm::cross(s, f);
	f = -f;
	glm::mat4 V = glm::mat4(s.x, s.y, s.z, -glm::dot(s, position),
							v.x, v.y, v.z, -glm::dot(v, position),
							f.x, f.y, f.z, glm::dot(f, position),
							0, -30, 100, 1);
	return V;
}

void Engine::Managers::SceneManager::refreshCamera()
{
	viewMatrix = lookAt(position, target, up);
}

glm::mat4 Engine::Managers::SceneManager::getPerspective(float width, float height, float n, float f, float angle)
{
	glm::mat4 p;
	float ar = width / height;
	p[0][0] = 1.0f / (ar * tan(angle / 2));
	p[1][1] = 1.0f / tan(angle / 2);
	p[2][2] = (-n - f) / (n - f);
	p[2][3] = 1.0f;
	p[3][2] = 2.0f * n * f / (n - f);

	return p;
}
