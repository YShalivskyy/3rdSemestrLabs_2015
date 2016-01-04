#pragma once
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
namespace Engine
{
	namespace Managers
	{

		class ShaderManager
		{
		public:

			ShaderManager(void);
			~ShaderManager(void);

			void createProgram(const std::string& shaderName,
				const std::string& VertexShaderFilename,
				const std::string& FragmentShaderFilename);

			static const GLuint getShader(const std::string&);

		private:
			std::string readShader(const std::string& filename);
			GLuint createShader(GLenum shaderType,
				const std::string& source,
				const std::string& shaderName);

			static std::map<std::string, GLuint> programs;

		};
	}
}
