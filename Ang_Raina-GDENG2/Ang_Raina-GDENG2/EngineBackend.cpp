#include "EngineBackend.h"

EngineBackend* EngineBackend::sharedInstance = nullptr;

EngineBackend* EngineBackend::getInstance()
{
	return sharedInstance;
}

void EngineBackend::initialize()
{
	sharedInstance = new EngineBackend();
}

void EngineBackend::destroy()
{
	delete sharedInstance;
}

void EngineBackend::SetMode(EditorMode mode)
{
	this->editorMode = mode;
}

void EngineBackend::StartFrameStep()
{
	this->frameStepping = true;
}

void EngineBackend::EndFrameStep()
{
	this->frameStepping = false;
}

bool EngineBackend::InsideFrameStep()
{
	return this->frameStepping;
}

EngineBackend::EditorMode EngineBackend::GetMode()
{
	return this->editorMode;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
