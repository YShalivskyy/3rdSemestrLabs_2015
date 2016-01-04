#pragma once
#include <iostream>
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "InitGlew.h"
#include "EventListener.h"
#include "DebugOutput.h"
namespace Engine
{
	namespace Core {
		namespace Init {

			class InitGlut {
			private:
				static Engine::Core::EventListener* listener;
				static Engine::Core::WindowInfo windowInformation;
				

				static float pressedX, pressedY, pressedZ;
				static bool leftButtonPressed, rightButtonPressed;

				static float xProjection(int x);
				static float yProjection(int y);
			public:
				static void setListener(Engine::Core::EventListener * listener);
				static void init(int &argc, char** argv, const Engine::Core::WindowInfo& window,
					const Engine::Core::ContextInfo& context,
					const Engine::Core::FrameBufferInfo& framebufferInfo);

			public:
				static void run();
				static void close();

				void enterFullscreen();
				void exitFullscreen();

				//used to print info about GL
				static void printOpenGLInfo(const Engine::Core::WindowInfo& windowInfo,
					const Engine::Core::ContextInfo& context);
			private:
				static void idleCallback(void);
				static void displayCallback(void);
				static void reshapeCallback(int width, int height);
				static void closeCallback();
				static void mouseCallback(int, int, int, int);
				static void mouseMotionCallback(int, int);
				static void wheelCallback(int, int, int, int);
			};
		}
	}
}
