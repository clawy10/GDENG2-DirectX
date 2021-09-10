#pragma once
#include <iostream>
#include <vector>
#include <stack>

class EditorAction;
class AGameObject;

class ActionHistory
{
public:
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void RecordAction(AGameObject* gameObject);
	bool HasRemainingUndoActions();
	bool HasRemainingRedoActions();
	EditorAction* UndoAction();
	EditorAction* RedoAction();
	void Clear();
	
private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};

	static ActionHistory* sharedInstance;

	std::stack<EditorAction*> actionsPerformed;
	std::stack<EditorAction*> actionsCancelled;
	
};

