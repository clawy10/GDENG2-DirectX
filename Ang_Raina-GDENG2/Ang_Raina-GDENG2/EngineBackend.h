#pragma once
#include <iostream>

class EngineBackend
{
public:
	static EngineBackend* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode
	{
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	void SetMode(EditorMode mode);
	void StartFrameStep();
	void EndFrameStep();
	bool InsideFrameStep();
	EditorMode GetMode();

private:
	EngineBackend();
	~EngineBackend();
	EngineBackend(EngineBackend const&) {};
	EngineBackend operator=(EngineBackend const&) {};

	static EngineBackend* sharedInstance;
	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;
	
};

