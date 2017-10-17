#include "App.h"

#include <iostream>

App::App()
	: m_Running(true)
	, m_Window(nullptr)
	, m_Renderer(nullptr)
	, m_Texture(nullptr)
	, m_ScreenBuffer(WindowWidth * WindowHeight * PixelByteSize, 0)
	, m_FrameStartTime(0)
	, m_FrameEndTime(0)
	, user(0, 36 , 10 , 72)
	, user2(150, 36 ,10 , 72)
{

}

App::~App()
{

}

void App::Init()
{
	SDL_Init(SDL_INIT_VIDEO);

	m_Window = SDL_CreateWindow("CGBEmu",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, 0);

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	m_Texture = SDL_CreateTexture(m_Renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowWidth, WindowHeight);

	PrintRendererInfo();
}

void App::Update()
{
	m_FrameStartTime = SDL_GetPerformanceCounter();

	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);
	///poe tudo a preto
	for (unsigned int i = 0; i < WindowWidth*WindowHeight; i++)
	{
		const unsigned int offset = PixelByteSize * i;
		m_ScreenBuffer[offset + 0] = 0;	//rand() % 256;        // b
		m_ScreenBuffer[offset + 1] = 0;	//rand() % 256;        // g
		m_ScreenBuffer[offset + 2] = 0;	//rand() % 256;        // r
		m_ScreenBuffer[offset + 3] = SDL_ALPHA_OPAQUE;    // a

	}
	//pinta o player1
	unsigned int x = user.get_x();
	unsigned int y = user.get_y();
	unsigned int w = user.get_width();
	unsigned int h = user.get_height();
	for (unsigned int j = 0; j < h; j++) {
		for (unsigned int k = 0; k < w; k++) {
			const unsigned int offset = (WindowWidth * PixelByteSize * (y+j)) + (x+k) * PixelByteSize;
			m_ScreenBuffer[offset + 0] = 150;			 // b
			m_ScreenBuffer[offset + 1] = 120;			 // g
			m_ScreenBuffer[offset + 2] = 120;        // r
			m_ScreenBuffer[offset + 3] = SDL_ALPHA_OPAQUE;    // a
		}
	}

	//pinta o player2
	unsigned int a = user2.get_x();
	unsigned int b = user2.get_y();
	unsigned int c = user2.get_width();
	unsigned int d = user2.get_height();
	for (unsigned int j = 0; j < d; j++) {
		for (unsigned int k = 0; k < c; k++) {
			const unsigned int offset = (WindowWidth * PixelByteSize * (b + j)) + (a + k) * PixelByteSize;
			m_ScreenBuffer[offset + 0] = 150;			 // b
			m_ScreenBuffer[offset + 1] = 120;			 // g
			m_ScreenBuffer[offset + 2] = 120;        // r
			m_ScreenBuffer[offset + 3] = SDL_ALPHA_OPAQUE;    // a
		}
	}

	moverplayers(h);
	
	/*unsigned int r1 = rand() % (WindowWidth-5);
	unsigned int r2 = rand() % (WindowHeight-5);

	for (unsigned int j = 0; j < 5; j++) {
		for (unsigned int k = 0; k < 5; k++) {
			const unsigned int offset = (WindowWidth * PixelByteSize * (r2 + j)) + (r1 + k) * PixelByteSize;
			m_ScreenBuffer[offset + 0] = 255;			 // b
			m_ScreenBuffer[offset + 1] = 255;			 // g
			m_ScreenBuffer[offset + 2] = 0;        // r
			m_ScreenBuffer[offset + 3] = SDL_ALPHA_OPAQUE;    // a
		}
	}*/
}

void App::Destroy()
{
	SDL_DestroyTexture(m_Texture);
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}

bool App::IsRunning() const
{
	return m_Running;
}

void App::PrintRendererInfo() const
{
	SDL_RendererInfo info;
	SDL_GetRendererInfo(m_Renderer, &info);
	std::cout << "Renderer name: " << info.name << std::endl;
	std::cout << "Texture formats: " << std::endl;
	for (uint32_t i = 0; i < info.num_texture_formats; i++)
	{
		std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << std::endl;
	}
}

void App::PrintFramerate() const
{
	const static uint64_t freq = SDL_GetPerformanceFrequency();
	const double seconds = (m_FrameEndTime - m_FrameStartTime) / static_cast<double>(freq);
	const int fps = static_cast<int>(1.0 / seconds);
	//std::cout << "Frame time: " << seconds * 1000.0 << "ms FPS: " << fps << std::endl;
}

void App::moverplayers(unsigned int h)
{
	SDL_Event event;
	SDL_UpdateTexture(m_Texture, NULL, m_ScreenBuffer.data(), WindowWidth * PixelByteSize);

	SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);

	while (SDL_PollEvent(&event))
	{
		/*if (event.type == SDL_QUIT)
		{
		m_Running = false;
		}*/
		switch (event.type)
		{
		case SDL_QUIT: {
			m_Running = false;
		}
					   break;

		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym)
			{
				/*case SDLK_LEFT: user.move_left();  break;

				case SDLK_RIGHT: {
				if (user.get_x() + w < WindowWidth - 1)
				{
				user.move_right();
				}
				}
				break;
				*/
				case SDLK_UP:	user.move_up(); break;

				case SDLK_DOWN: {
					if (user.get_y() + h < WindowHeight - 1)
					{
						user.move_down();
					}
				} break;
				
				case SDLK_w:	user2.move_up(); break;

				case SDLK_s: {
					if (user2.get_y() + h < WindowHeight - 1)
					{
						user2.move_down();
					}
				}
			}
		} break;
		}
	}
	m_FrameEndTime = SDL_GetPerformanceCounter();

	PrintFramerate();
}