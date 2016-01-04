#pragma once
#include <string>

#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_POSITION_X 100
#define DEFAULT_WONDOW_POSITION_Y 100
#define DEFAULT_WINDOW_NAME "OpenGL Window"
//WindowInfo.h
namespace Engine
{
	namespace Core
	{
		struct WindowInfo
		{
			std::string name;
			int width, height;
			int positionX, positionY;
			bool isReshapable;
			/*
				Default constructor
			*/
			WindowInfo()
			{
				name = DEFAULT_WINDOW_NAME;
				width = DEFAULT_WINDOW_WIDTH; height = DEFAULT_WINDOW_HEIGHT;
				positionX = DEFAULT_WINDOW_POSITION_X;
				positionY = DEFAULT_WONDOW_POSITION_Y;
				isReshapable = true;
			}

			WindowInfo(std::string name,
				int startPositionX, int startPositionY,
				int width, int height,
				bool isReshapable)
			{

				this->name = name;
				this->positionX = startPositionX;
				this->positionY = startPositionY;

				this->width = width;
				this->height = height;
				this->isReshapable = isReshapable;
			}

			/*
				Copying constructor
			*/
			WindowInfo(const WindowInfo& windowInfo)
			{
				name = windowInfo.name;
				positionX = windowInfo.positionX;
				positionY = windowInfo.positionY;

				width = windowInfo.width;
				height = windowInfo.height;
				isReshapable = windowInfo.isReshapable;
			}
			/*
				Copying operator
			*/
			void operator=(const WindowInfo& windowInfo)
			{

				name = windowInfo.name;

				positionX = windowInfo.positionX;
				positionY = windowInfo.positionX;

				width = windowInfo.width;
				height = windowInfo.height;
				isReshapable = windowInfo.isReshapable;
			}

		};
	}
}