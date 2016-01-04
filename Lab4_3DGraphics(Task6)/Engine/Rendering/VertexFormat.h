#pragma once
#ifndef  VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp" //installed with NuGet
namespace Engine
{
	namespace Rendering
	{
		struct VertexFormat
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texture;

			VertexFormat(const glm::vec3 &pos, const glm::vec4 &color)
			{
				this->position = pos;
				this->color = color;
			}

			VertexFormat(const glm::vec3 &pos, const glm::vec2 &texture)
			{
				this->position = pos;
				this->texture = texture;
				color.r = color.g = color.b = color.a = 0;
			}
			VertexFormat() {}
		};
	}
}



#endif