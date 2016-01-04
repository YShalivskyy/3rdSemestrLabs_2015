#pragma once
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../GameObject.h"

namespace Engine
{
	namespace Rendering
	{
		namespace Models
		{
			class Model :public GameObject
			{
			public:
				Model();
				virtual ~Model();
				// methods from interface
				virtual void draw() override;
				virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;
				virtual void update() override;
				virtual void setProgram(GLuint shaderName) override;
				virtual void destroy() override;

				virtual GLuint getVao() const override;
				virtual const std::vector<GLuint>& getVbos() const override;

				virtual const GLuint getTexture(std::string textureName) const override;
				virtual void setTexture(std::string textureName, GLuint texture) override;

				virtual void translate(glm::vec3 translation) override;
				virtual void translateCamera(glm::vec3 translation) override;
				virtual void rotateCamera(glm::vec3 rotation) override;
				//virtual void rotate(glm::vec3 rotation) override;

				virtual void launchObject(glm::vec3 force) override;
			protected:
				GLuint vao;
				GLuint program;
				std::vector<GLuint> vbos;
				glm::vec3 cameraPosition;
				glm::vec3 cameraRotation;
				glm::vec3 position;
				std::map<std::string, GLuint> textures;

				glm::vec3 speed; 
			};
		}
	}
}