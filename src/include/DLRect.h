#pragma once

namespace DontLaugh
{
	struct DLRect
	{
	public:
		int X;
		int Y;
		int Width;
		int Height;

	public:
		DLRect();
		DLRect(int X, int Y, int Width, int Height);

	};

	DLRect::DLRect() : X(0), Y(0), Width(0), Height(0)
	{
	}

	DLRect::DLRect(int X, int Y, int Width, int Height) : X(X), Y(Y), Width(Width), Height(Height)
	{
	}
}