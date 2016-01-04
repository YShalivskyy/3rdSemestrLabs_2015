#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include "VertexFormat.h"

namespace Engine
{
	namespace Rendering
	{
		class GameObject
		{
		public:
			virtual ~GameObject() = 0;

			virtual void draw() = 0;
			virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;
			virtual void update() = 0;
			virtual void setProgram(GLuint shaderName) = 0;
			virtual void destroy() = 0;
			virtual void translate(glm::vec3 translation) = 0;
			virtual void translateCamera(glm::vec3 translation) = 0;
			virtual void rotateCamera(glm::vec3 rotation) = 0;
			//virtual void rotate(glm::vec3 rotation) = 0;

			virtual void setTexture(std::string textureName, GLuint texture) = 0;
			virtual const GLuint getTexture(std::string textureName) const = 0;

			virtual GLuint getVao() const = 0;
			virtual const std::vector<GLuint>& getVbos() const = 0;

			virtual void launchObject(glm::vec3 force) = 0; // param - vector of direction of force


		};

		inline GameObject::~GameObject(){}
	}
}