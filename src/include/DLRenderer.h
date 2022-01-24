#pragma once

#include <functional>
#include "SDL.h"
#include "DLPoint.h"

namespace DontLaugh
{
	/* Soft renderer implemented by DontLaugh */
	class DLRenderer
	{
	public:
		DLRenderer();
		DLRenderer(int Width, int Height);
		~DLRenderer();

		void RenderLoop(const std::function<void(SDL_Event&)>& Callback) const;
		void SetRenderColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A) const;
		void DrawPixel(int X, int Y) const;
		void DrawLine(int X0, int Y0, int X1, int Y1) const;
		void DrawTriangle(DLPoint* Points) const;

		Uint32 GetTicks() const { return SDL_GetTicks(); }

	private:
		static Uint32 fps;
		static Uint32 last_time;
		static Uint32 frame_count;

		SDL_Window* window;
		SDL_Renderer* renderer;
		std::string title;
	};
}
