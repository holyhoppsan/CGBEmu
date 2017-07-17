#include <iostream>
#include <vector>

#include <SDL.h>

#include "App.h"

int main(int argc, char *args[])
{
	std::cout << "CGBEmu" << std::endl;

	App app;

	app.Init();

	while (app.IsRunning())
	{
		app.Update();
	}
	
	app.Destroy();

    return 0;
}

