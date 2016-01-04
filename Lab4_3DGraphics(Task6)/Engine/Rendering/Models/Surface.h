#pragma once
#include "Model.h"
#include <time.h>
#include <stdarg.h>


namespace Engine
{
	namespace Rendering
	{
		namespace Models
		{

			class Surface : public Model
			{
			public:
				Surface();
				Surface(float);
				~Surface();

				void create();
				virtual void draw(const glm::mat4& projection_matrix,
					const glm::mat4& view_matrix) override final;
				virtual void update() override final;

			private:
				float surfaceLevel;
				time_t timer;
			};
		}
	}
}