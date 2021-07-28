#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (sharedInstance != nullptr)
	{
		delete sharedInstance;
	}
}

void InputSystem::AddListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::Update()
{
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	if (this->firstTime)
	{
		this->oldMousePos = Point(currentMousePos.x, currentMousePos.y);
		this->firstTime = false;
	}
	
	if (currentMousePos.x != this->oldMousePos.x || currentMousePos.y != this->oldMousePos.y)
	{
		// mouse move event
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
		while (it != m_set_listeners.end())
		{
			(*it)->OnMouseMove(Point(currentMousePos.x, currentMousePos.y));
			it++;
		}
	}

	this->oldMousePos = Point(currentMousePos.x, currentMousePos.y);

	
	
	if(::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				while (it != m_set_listeners.end()) 
				{
					// left mouse button 
					if (i == VK_LBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
						{
							(*it)->OnLeftMouseDown(Point(currentMousePos.x - this->oldMousePos.x, currentMousePos.y - this->oldMousePos.y));
						}
					}
					// right mouse button 
					if (i == VK_RBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
						{
							(*it)->OnRightMouseDown(Point(currentMousePos.x - this->oldMousePos.x, currentMousePos.y - this->oldMousePos.y));
						}
					}
					else
					{
						(*it)->OnKeyDown(i);
					}
					it++;
				}
			}
			// KEY IS UP
			else
			{
				if (keysState[i] != oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
					while (it != m_set_listeners.end()) 
					{
						if (i == VK_LBUTTON)
						{
							(*it)->OnLeftMouseUp(Point(currentMousePos.x - this->oldMousePos.x, currentMousePos.y - this->oldMousePos.y));
						}
						else if (i == VK_RBUTTON)
						{
							(*it)->OnRightMouseUp(Point(currentMousePos.x - this->oldMousePos.x, currentMousePos.y - this->oldMousePos.y));
						}
						else
						{
							(*it)->OnKeyUp(i);
						}
						it++;
					}
				}
			}
		}
		// store current key states
		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
	}
}

void InputSystem::SetCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::ShowCursor(bool flag)
{
	::ShowCursor(flag);
}
