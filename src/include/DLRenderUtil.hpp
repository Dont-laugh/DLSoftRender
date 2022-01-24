#pragma once

#include <cmath>
#include "SDL.h"
#include "DLPoint.h"
#include "DLRect.h"

namespace DontLaugh
{
	/** Utility for DLRenderer */
	static class DLRenderUtil
	{
	public:
		/* DDA Algorithm */
		static void DDA_DrawLine(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);

		/* Bresenham Algorithm Raw Version */
		static void Bresenham_DrawLineV1(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);

		/* Bresenham Algorithm Improved Version */
		static void Bresenham_DrawLineV2(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);

		/* Simplified Algorithm Improved Version */
		static void Bresenham_DrawLineV3(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1);

		/* Calculate AABB */
		static DLRect& CalcAABB(DLPoint& P1, DLPoint& P2, DLPoint& P3);

		/* Barycentric coordinates draw triangle */
		static void Barycentric_DrawTriangle(SDL_Renderer* const renderer, DLPoint* Points);
	};

	void DLRenderUtil::DDA_DrawLine(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
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

	void DLRenderUtil::Bresenham_DrawLineV1(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
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

	void DLRenderUtil::Bresenham_DrawLineV2(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
	{
		int dx = X1 - X0;
		int dy = Y1 - Y0;

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
			int e = -dx;
			for (int x = X0; x <= X1; ++x)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				e += 2 * dy;
				if (e > 0)
				{
					++y;
					e -= 2 * dx;
				}
			}
		}
		else
		{
			int x = X0;
			int e = -dy;
			for (int y = Y0; y < Y1; ++y)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				e += 2 * dx;
				if (e > 0)
				{
					++x;
					e -= 2 * dy;
				}
			}
		}
	}

	void DLRenderUtil::Bresenham_DrawLineV3(SDL_Renderer* const renderer, int X0, int Y0, int X1, int Y1)
	{
		int dx = abs(X1 - X0);
		int sx = X0 < X1 ? 1 : -1;
		int dy = abs(Y1 - Y0);
		int sy = Y0 < Y1 ? 1 : -1;
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

	inline DLRect& DLRenderUtil::CalcAABB(DLPoint& P1, DLPoint& P2, DLPoint& P3)
	{
		int MinX = std::min(std::min(P1.X, P2.X), P3.X);
		int MinY = std::min(std::min(P1.Y, P2.Y), P3.Y);
		int MaxX = std::max(std::max(P1.X, P2.X), P3.X);
		int MaxY = std::max(std::max(P1.Y, P2.Y), P3.Y);
		return DLRect(MinX, MinY, MaxX, MaxY);
	}
}