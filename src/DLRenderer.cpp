#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include "SDL.h"
#include "DLRenderer.h"

using namespace DontLaugh;


static void DDA_DrawLine(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);
static void Bresenham_DrawLineV1(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);
static void Bresenham_DrawLineV2(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);


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
	//SDL_RenderDrawLine(renderer, X0, Y0, X1, Y1);

	//DDA_DrawLine(renderer, X0, Y0, X1, Y1);
	Bresenham_DrawLineV1(renderer, X0, Y0, X1, Y1);
}

void DLRenderer::DrawTriangle(DLPoint* Points) const
{
	SDL_assert(renderer != nullptr);
}

/// <summary>
/// DDA Algorithm
/// </summary>
void DDA_DrawLine(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	float x = X0;
	float y = Y0;

	int absX = std::abs(dx);
	int absY = std::abs(dy);

	// Judge max offset direction
	int mDis = absX > absY ? absX : absY;

	// Single step in X & Y
	float xInc = (float)dx / mDis;
	float yInc = (float)dy / mDis;

	for (auto k = 0; k <= mDis; k++)
	{
		SDL_RenderDrawPoint(renderer, (int)(x + 0.5f), (int)(y + 0.5f));
		x += xInc;
		y += yInc;
	}
}

/// <summary>
/// Bresenham Algorithm Raw Version
/// </summary>
void Bresenham_DrawLineV1(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int d = dx - 2 * dy;

	if (dx < 0)
	{
		std::swap(X0, X1);
		dx = -dx;
	}
	if (dy < 0)
	{
		std::swap(Y0, Y1);
		dy = -dy;
	}

	if (dx > dy)
	{
		int y = Y0;
		for (int x = X0; x <= X1; ++x)
		{
			SDL_RenderDrawPoint(renderer, x, y);
			if (d < 0)
			{
				++y;
				d += 2 * dx - 2 * dy;
			}
			else
			{
				d -= 2 * dy;
			}
		}
	}
	else
	{
		int x = X0;
		for (int y = Y0; y <= Y1; ++y)
		{
			SDL_RenderDrawPoint(renderer, x, y);
			if (d < 0)
			{
				++x;
				d += 2 * dy - 2 * dx;
			}
			else
			{
				d -= 2 * dx;
			}
		}
	}
}

/// <summary>
/// Bresenham Algorithm Improved Version
/// </summary>
void Bresenham_DrawLineV2(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
{
	int dx = abs(X1 - X0), sx = X0 < X1 ? 1 : -1;
	int dy = abs(Y1 - Y0), sy = Y0 < Y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	while (true)
	{
		SDL_RenderDrawPoint(renderer, X0, Y0);
		if (X0 == X1 && Y0 == Y1) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; X0 += sx; }
		if (e2 < dy) { err += dx; Y0 += sy; }
	}
}
