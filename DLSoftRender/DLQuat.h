#pragma once

#include "DLVector.h"

namespace DontLaugh
{
	struct DLQuat
	{
	public:
		float X;
		float Y;
		float Z;
		float W;

	public:
		DLQuat();
		DLQuat(float InX, float InY, float InZ, float InW);
		DLQuat(DLVector Axis, float AngleRad);
	};
}
