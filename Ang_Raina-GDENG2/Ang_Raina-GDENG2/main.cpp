#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* app = (AppWindow*)AppWindow::getInstance();

	while (app->isRun())
	{
		app->broadcast();
	}
	return 0;
}