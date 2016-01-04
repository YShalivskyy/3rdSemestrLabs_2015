#pragma once

#include <iostream>
#include <glew\glew.h>
#include <freeglut\freeglut.h>

namespace Engine
{
	namespace Core {

		namespace Init {

			class InitGlew
			{
			public:
				static void init();
			};
		}
	}
}
