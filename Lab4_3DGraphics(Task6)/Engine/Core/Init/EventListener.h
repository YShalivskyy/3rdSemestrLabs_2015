#pragma once
namespace Engine
{
	namespace Core {

		
		class EventListener
		{
		public:
			virtual ~EventListener() = 0;

			virtual void notifyBeginFrame() = 0;
			virtual void notifyDisplayFrame() = 0;
			virtual void notifyEndFrame() = 0;
			virtual void notifyReshape(int width,
				int height,
				int previous_width,
				int previous_height) = 0;
			virtual void notifyTranslation(float, float, float) = 0;
			virtual void notifyRotation(float, float, float) = 0;
			virtual void notifyLaunch(float, float, float) = 0;
		};

		inline EventListener::~EventListener() {}
	}
}
