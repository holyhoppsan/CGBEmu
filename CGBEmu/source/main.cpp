#include <iostream>
#include <vector>

#include <SDL.h>

#include "Player.h"

#include "App.h"

int main(int argc, char *args[])
{
	std::cout << "CGBEmu" << std::endl;
	std::cout << "Args: " << argc << "arg array: " << args << std::endl;
	
	App app;

	app.Init();

	while (app.IsRunning())
	{
		app.Update();
	}
	
	app.Destroy();
	
    return 0;
}

