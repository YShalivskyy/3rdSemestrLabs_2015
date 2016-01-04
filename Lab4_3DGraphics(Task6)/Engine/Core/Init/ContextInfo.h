#pragma once
//ContextInfo.h
namespace Engine
{
	namespace Core {

		//OpenGL versions
		struct ContextInfo
		{
			int majorVersion, minorVersion; 
			bool core;

			/*
				Default constructor
			*/
			ContextInfo()
			{
				majorVersion = 4;
				minorVersion = 3;
				core = true;
			}

			ContextInfo(int majorVersion, int minorVersion, bool core)
			{
				this->majorVersion = majorVersion;
				this->minorVersion = minorVersion;
				this->core = core;
			}

			/*
				Copying constructor
			*/
			ContextInfo(ContextInfo &contextInfo)
			{
				this->majorVersion = contextInfo.majorVersion;
				this->minorVersion = contextInfo.minorVersion;
				this->core = contextInfo.core;
			}

			/*
				Copying operator
			*/
			void operator=(ContextInfo &contextInfo)
			{
				this->majorVersion = contextInfo.majorVersion;
				this->minorVersion = contextInfo.minorVersion;
				this->core = contextInfo.core;
			}
		};
	}
}
