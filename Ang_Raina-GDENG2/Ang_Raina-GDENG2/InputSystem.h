#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

public:
	void AddListener(InputListener* listener);
	void RemoveListener(InputListener* listener);

	void Update();

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};
	static InputSystem* sharedInstance;
	
private:
	std::unordered_set<InputListener*> m_set_listeners;
	
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};

	Point oldMousePos;
	bool firstTime = true;
};

