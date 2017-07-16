#pragma once

#include <SDL.h>
#include <vector>

constexpr int WindowWidth = 160;
constexpr int WindowHeight = 144;
constexpr int PixelByteSize = 4;

class App
{
public:

	App();
	~App();

	void Init();
	void Update();
	void Destroy();

	bool IsRunning() const;

private:

	void PrintRendererInfo() const;
	void PrintFramerate() const;

	bool m_Running;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;

	std::vector< unsigned char > m_ScreenBuffer;

	uint64_t m_FrameStartTime;
	uint64_t m_FrameEndTime;

};