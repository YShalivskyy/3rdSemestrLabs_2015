#pragma once
#include "CustomEngine.h"

using namespace Engine;
using namespace Rendering::Models;
int main(int argc, char **argv)
{
	CustomEngine* engine = new CustomEngine();
	engine->init(argc, argv);

	Sphere * s1 = new Sphere(glm::vec3(0, 5, -3));
	Surface * surface = new Surface(-3);

	engine->getShaderManager()->createProgram("sphereProgram",
		"Shaders\\SphereVertexShader.glsl",
		"Shaders\\SphereFragmentShader.glsl");

	// setting shaders and creating models (a surface and sphere) 
	s1->setProgram(engine->getShaderManager()->getShader(DEFAULT_PROGRAM));
	s1->create();
	surface->setProgram(engine->getShaderManager()->getShader(DEFAULT_PROGRAM));
	surface->create();

	engine->getModelManager()->setModel("surface", surface);
	engine->getModelManager()->setModel("sphere1", s1);

	// initializing speed vector with ways values
	s1->push(glm::vec3(0.1, 0, 0.2));

	// launch the glut engine 
	engine->run();


	delete engine;
	return 0;
}