#pragma once

#include <cmath>

namespace DontLaugh
{
	/* 3D Vector by DontLaugh */
	struct DLVector
	{
	public:
		float X;
		float Y;
		float Z;

	public:
		DLVector();
		DLVector(float InF);
		DLVector(float X, float Y, float Z);

		static const DLVector Zero;
		static const DLVector One;

		static DLVector Cross(const DLVector& A, const DLVector& B);
		static float Dot(const DLVector& A, const DLVector& B);

		float Length() const;
		bool Equals(const DLVector& V) const;

		DLVector operator+(const DLVector& V);
		DLVector operator-(const DLVector& V);
		DLVector operator*(const DLVector& V);
		DLVector operator/(const DLVector& V);

	private:
		static float epsilon;
	};

	const DLVector DLVector::Zero(0, 0, 0);
	const DLVector DLVector::One(1, 1, 1);
	float DLVector::epsilon = 1e-5;

	inline DLVector::DLVector() : X(0), Y(0), Z(0) { }

	inline DLVector::DLVector(float InF) : X(InF), Y(InF), Z(InF) { }

	inline DLVector::DLVector(float X, float Y, float Z) : X(X), Y(Y), Z(Z) { }

	inline DLVector DLVector::Cross(const DLVector& A, const DLVector& B)
	{
		return DLVector
		(
			A.Y * B.Z - A.Z * B.Y,
			A.Z * B.X - A.X * B.Z,
			A.X * B.Y - A.Y * B.X
		);
	}

	inline float DLVector::Dot(const DLVector& A, const DLVector& B)
	{
		return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
	}

	inline float DLVector::Length() const
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}

	inline bool DLVector::Equals(const DLVector& V) const
	{
		return abs(X - V.X) <= epsilon && abs(Y - V.Y) <= epsilon && abs(Z - V.Z) <= epsilon;
	}

	inline DLVector DLVector::operator+(const DLVector& V)
	{
		return DLVector(X + V.X, Y + V.Y, Z + V.Z);
	}

	inline DLVector DLVector::operator-(const DLVector& V)
	{
		return DLVector(X - V.X, Y - V.Y, Z - V.Z);
	}

	inline DLVector DLVector::operator*(const DLVector& V)
	{
		return DLVector(X * V.X, Y * V.Y, Z * V.Z);
	}

	inline DLVector DLVector::operator/(const DLVector& V)
	{
		return DLVector(X / V.X, Y / V.Y, Z / V.Z);
	}
}
