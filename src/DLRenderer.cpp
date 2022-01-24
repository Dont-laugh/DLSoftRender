#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include "SDL.h"
#include "DLRenderer.h"
#include "DLRenderUtil.hpp"

using namespace DontLaugh;

Uint32 DLRenderer::fps = 0;
Uint32 DLRenderer::last_time = 0;
Uint32 DLRenderer::frame_count = 0;

DLRenderer::DLRenderer() : DLRenderer(800, 600)
{
}

DLRenderer::DLRenderer(const int Width, const int Height) : window(nullptr), renderer(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL could not initialized with error: " << SDL_GetError() << std::endl;
		return;
	}

	title = "DL SoftRender";

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		std::cerr << "SDL could not create window with error: " << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cerr << "SDL could not create renderer with error: " << SDL_GetError() << std::endl;
		return;
	}
}

DLRenderer::~DLRenderer()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
}

void DLRenderer::RenderLoop(const std::function<void(SDL_Event&)>& Callback) const
{
	SDL_Event sdl_event;

	while (true)
	{
		if (SDL_PollEvent(&sdl_event) && sdl_event.type == SDL_QUIT)
		{
			std::cout << "SDL quit!" << std::endl;
			break;
		}

		// Calculate fps
		Uint32 const curr_time = GetTicks();
		++frame_count;

		if (curr_time - last_time > 1000)
		{
			fps = frame_count;
			frame_count = 0;
			last_time = curr_time;

			std::stringstream ss;
			ss << title << " (fps: " << fps << ")";
			SDL_SetWindowTitle(window, ss.str().c_str());
		}

		// Draw background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		// Callback function
		if (Callback != nullptr)
		{
			Callback(sdl_event);
		}

		// Update screen
		SDL_RenderPresent(renderer);
	}
}

void DLRenderer::SetRenderColor(const Uint8 R, const Uint8 G, const Uint8 B, const Uint8 A) const
{
	SDL_assert(renderer != nullptr);
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
}

void DLRenderer::DrawPixel(const int X, const int Y) const
{
	SDL_assert(renderer != nullptr);
	SDL_RenderDrawPoint(renderer, X, Y);
}

void DLRenderer::DrawLine(const int X0, const int Y0, const int X1, const int Y1) const
{
	SDL_assert(renderer != nullptr);
	DLRenderUtil::Bresenham_DrawLineV3(renderer, X0, Y0, X1, Y1);
}

void DLRenderer::DrawTriangle(DLPoint* Points) const
{
	SDL_assert(renderer != nullptr);

}
