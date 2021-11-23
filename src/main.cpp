#include <iostream>
#include "DLRenderer.h"

using namespace std;
using namespace DontLaugh;


int main(int argc, char** argv)
{
	constexpr int WIDTH = 1000, HEIGHT = 700;
	const auto renderer = new DLRenderer(WIDTH, HEIGHT);

	renderer->RenderLoop([=](SDL_Event&)
		{
			renderer->SetRenderColor(0x00, 0xFF, 0xFF, 0xFF);

			renderer->DrawLine(100, -65, 800, 600);
			renderer->DrawLine(400, 200, 65, 100);
		});

	delete renderer;

	return 0;
}
