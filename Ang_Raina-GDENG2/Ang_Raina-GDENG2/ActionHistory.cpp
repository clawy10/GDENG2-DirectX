#include "ActionHistory.h"
#include "EngineBackend.h"
#include "EditorAction.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
}

void ActionHistory::RecordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->GetMode() == EngineBackend::EDITOR)
	{
		EditorAction* editorAction = new EditorAction(gameObject);
		this->actionsPerformed.push(editorAction);
	}
}

bool ActionHistory::HasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::HasRemainingRedoActions()
{
	return !this->actionsCancelled.empty();
}

EditorAction* ActionHistory::UndoAction()
{
	if (this->HasRemainingUndoActions())
	{
		EditorAction* editorAction = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(editorAction);
		return editorAction;
	}
	return nullptr;
}

EditorAction* ActionHistory::RedoAction()
{
	if (this->HasRemainingRedoActions())
	{
		EditorAction* editorAction = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(editorAction);
		return editorAction;
	}
	return nullptr;
}

void ActionHistory::Clear()
{
	while (this->HasRemainingUndoActions())
	{
		EditorAction* editorAction = this->actionsPerformed.top();
		delete editorAction;
		this->actionsPerformed.pop();
	}
	while (this->HasRemainingRedoActions())
	{
		EditorAction* editorAction = this->actionsCancelled.top();
		delete editorAction;
		this->actionsCancelled.pop();
	}
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
	this->Clear();
}
