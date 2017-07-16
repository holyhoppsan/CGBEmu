#include <iostream>
#include <SDL.h>

int main(int argc, char *args[])
{
	auto result = SDL_Init(SDL_INIT_VIDEO);

    std::cout << "CGBEmu" << std::endl;

	SDL_Quit();
    return result;
}