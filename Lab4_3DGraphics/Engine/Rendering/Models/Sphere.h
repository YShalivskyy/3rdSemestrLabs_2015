#pragma once
#include "Model.h"
#include <time.h>
#include <stdarg.h>
#define DEFAULT_SPHERE_VERTEX_COUNT 360
#define DEFAULT_SPHERE_RADIUS 2
#define GRAVITY 0.01

namespace Engine
{
	namespace Rendering
	{
		namespace Models
		{

			class Sphere : public Model
			{
			public:
				Sphere();
				Sphere(float);
				Sphere(glm::vec3);
				Sphere(glm::vec3, float);
				Sphere(glm::vec3, unsigned int, float);
				~Sphere();

				void create();
				virtual void draw(const glm::mat4& projection_matrix,
					const glm::mat4& view_matrix) override final;
				virtual void update() override final;
				bool surfaceTouch();
				void push(glm::vec3 speed);

			private:
				unsigned int vertexCount;
				float radius;
				time_t timer;
			};
		}
	}
}
