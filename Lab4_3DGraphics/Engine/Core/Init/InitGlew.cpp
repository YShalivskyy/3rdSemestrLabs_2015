#include "InitGlew.h"
using namespace Engine::Core;
using namespace Engine::Core::Init;

void InitGlew::init() 
{

	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialize" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << "GLEW GL_VERSION_4_3 is 4.3\n ";
	}
	else
	{
		std::cout << " GLEW GL_VERSION_4_3 not supported\n ";
	}
}