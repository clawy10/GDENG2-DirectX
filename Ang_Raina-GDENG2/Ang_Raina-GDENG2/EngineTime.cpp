#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::GetDeltaTime()
{
	return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
	
}

EngineTime::~EngineTime()
{
	
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedSeconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsedSeconds.count();
}
