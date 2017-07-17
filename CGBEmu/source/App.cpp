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
	SDL_Event event;

	m_FrameStartTime = SDL_GetPerformanceCounter();

	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);

	for (unsigned int i = 0; i < 1000; i++)
	{
		const unsigned int x = rand() % WindowWidth;
		const unsigned int y = rand() % WindowHeight;

		const unsigned int offset = (WindowWidth * PixelByteSize * y) + x * PixelByteSize;
		m_ScreenBuffer[offset + 0] = rand() % 256;        // b
		m_ScreenBuffer[offset + 1] = rand() % 256;        // g
		m_ScreenBuffer[offset + 2] = rand() % 256;        // r
		m_ScreenBuffer[offset + 3] = SDL_ALPHA_OPAQUE;    // a
	}

	SDL_UpdateTexture(m_Texture, NULL, m_ScreenBuffer.data(), WindowWidth * PixelByteSize);

	SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_Running = false;
		}
	}

	m_FrameEndTime = SDL_GetPerformanceCounter();

	PrintFramerate();
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
	const double seconds = (m_FrameEndTime - m_FrameStartTime) / static_cast< double >(freq);
	const int fps = static_cast<int>(1.0 / seconds);
	std::cout << "Frame time: " << seconds * 1000.0 << "ms FPS: " << fps << std::endl;
}