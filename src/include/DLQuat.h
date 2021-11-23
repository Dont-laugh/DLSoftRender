#pragma once

#include "DLVector3.h"


namespace DontLaugh
{
	/* Quaternion implemented by DontLaugh */
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
		DLQuat(DLVector3 Axis, float AngleRad);

		static const DLQuat Identity;
	};
}
