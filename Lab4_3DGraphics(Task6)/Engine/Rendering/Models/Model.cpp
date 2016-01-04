#include "Model.h"
using namespace Engine::Rendering;
using namespace Models;

Model::Model() {}

Model::~Model()
{
	destroy();
}

void Model::draw()
{
}

void Engine::Rendering::Models::Model::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
{
}

void Model::update()
{
}

void Model::setProgram(GLuint program)
{
	this->program = program;
}

GLuint Model::getVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::getVbos() const
{
	return vbos;
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();

	if (textures.size() > 0)
	{
		for (auto t : textures)
		{
			glDeleteTextures(1, &t.second);
		}
		textures.clear();
	}
}

const GLuint Model::getTexture(std::string textureName) const
{
	return textures.at(textureName);
}

void Model::setTexture(std::string textureName, GLuint texture)
{
	if (texture == 0) return;
	textures[textureName] = texture;
}

void Model::translate(glm::vec3 translation)
{
	position += translation;
}

void Engine::Rendering::Models::Model::translateCamera(glm::vec3 translation)
{
	cameraPosition += translation;
}

void Engine::Rendering::Models::Model::rotateCamera(glm::vec3 rotation)
{
	cameraRotation += rotation;
}

void Engine::Rendering::Models::Model::launchObject(glm::vec3 force)
{
	speed += force;
}
