#include "InitGlut.h"
using namespace Engine::Core::Init;

Engine::Core::EventListener* InitGlut::listener = NULL;
Engine::Core::WindowInfo InitGlut::windowInformation;

float InitGlut::pressedX = 0;
float InitGlut::pressedY = 0;
float InitGlut::pressedZ = 0;

bool InitGlut::leftButtonPressed = false;
bool InitGlut::rightButtonPressed = false;



void InitGlut::init(int &argc, char **argv, const Engine::Core::WindowInfo& windowInfo,
	const Engine::Core::ContextInfo& contextInfo,
	const Engine::Core::FrameBufferInfo& framebufferInfo)
{
	glutInit(&argc, argv);
	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);


	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.positionX, windowInfo.positionY);
	glutInitWindowSize(windowInfo.width, windowInfo.height);
	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: initialized" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);

	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotionCallback);
	glutMouseWheelFunc(wheelCallback);

	Init::InitGlew::init();

	glDebugMessageCallback(DebugOutput::debugCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	windowInformation = windowInfo;
	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);
}


//Starts the rendering loop
void Engine::Core::Init::InitGlut::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Engine::Core::Init::InitGlut::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Engine::Core::Init::InitGlut::enterFullscreen()
{
}


void Engine::Core::Init::InitGlut::exitFullscreen()
{
}

void Engine::Core::Init::InitGlut::printOpenGLInfo(const Engine::Core::WindowInfo & windowInfo, const Engine::Core::ContextInfo & context)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}

//Redisplaying
void Engine::Core::Init::InitGlut::idleCallback(void)
{
	glutPostRedisplay();
}

void Engine::Core::Init::InitGlut::displayCallback(void)
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Engine::Core::Init::InitGlut::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
			windowInformation.width = width;
			windowInformation.height = height;
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Engine::Core::Init::InitGlut::closeCallback()
{
	close();
}

void Engine::Core::Init::InitGlut::mouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			rightButtonPressed = true;
			InitGlut::pressedX = xProjection(x);
			InitGlut::pressedY = yProjection(y);
		}
		else
			rightButtonPressed = false;
	}
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			leftButtonPressed = true;
			InitGlut::pressedX = xProjection(x);
			InitGlut::pressedY = yProjection(y);
		}
		else
		{
			listener->notifyLaunch(-(InitGlut::pressedX - xProjection(x)) / 50, (InitGlut::pressedY - yProjection(y)) / 50, 0.0);
			leftButtonPressed = false;
		}
			
	}
}

void Engine::Core::Init::InitGlut::mouseMotionCallback(int x, int y)
{
	if (rightButtonPressed)
	{
		if (leftButtonPressed)
		{
		}
		else
		{
			listener->notifyRotation(-(InitGlut::pressedY - yProjection(y)) / 10, (InitGlut::pressedX - xProjection(x)) / 10, 0.0);
			InitGlut::pressedX = xProjection(x);
			InitGlut::pressedY = yProjection(y);
		}
	}
	else if (leftButtonPressed)
	{
		//listener->notifyLaunch((InitGlut::pressedX - xProjection(x)) / 100, (InitGlut::pressedY - yProjection(y)) / 100, 0.0);
		//listener->notifyLaunch((InitGlut::pressedX - xProjection(x)) / 100, (InitGlut::pressedY - yProjection(y)) / 100, 0.0);
		//InitGlut::pressedX = xProjection(x);
		//InitGlut::pressedY = yProjection(y);
	}
}

void Engine::Core::Init::InitGlut::wheelCallback(int wheel, int direction, int x, int y)
{
	if (direction > 0)
		listener->notifyTranslation(0.0f, 0.0f, -0.3f);
	else
		listener->notifyTranslation(0.0f, 0.0f, 0.3f);
}

float Engine::Core::Init::InitGlut::xProjection(int x)
{
	return x - windowInformation.width / 2.0f;
}

float Engine::Core::Init::InitGlut::yProjection(int y)
{
	return windowInformation.height / 2.0f - y;
}

void Engine::Core::Init::InitGlut::setListener(Engine::Core::EventListener * listener)
{
	InitGlut::listener = listener;
}