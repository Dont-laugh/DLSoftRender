#pragma once

#include <cmath>


namespace DontLaugh
{
	/* 2D Vector implemented by DontLaugh */
	struct DLVector2
	{
	public:
		float X;
		float Y;

	public:
		DLVector2();
		DLVector2(float InF);
		DLVector2(float X, float Y);

		static const DLVector2 Zero;
		static const DLVector2 One;

		static DLVector2 Cross(const DLVector2& A, const DLVector2& B);
		static float Dot(const DLVector2& A, const DLVector2& B);

		float Length() const;
		bool Equals(const DLVector2& V) const;

		DLVector2 operator+(const DLVector2& V);
		DLVector2 operator-(const DLVector2& V);
		DLVector2 operator*(const DLVector2& V);
		DLVector2 operator/(const DLVector2& V);

	private:
		static const float epsilon;
	};


	const DLVector2 DLVector2::Zero(0, 0);
	const DLVector2 DLVector2::One(1, 1);
	constexpr  float DLVector2::epsilon = 1e-4f;

	inline DLVector2::DLVector2() : X(0), Y(0) { }

	inline DLVector2::DLVector2(float InF) : X(InF), Y(InF) { }

	inline DLVector2::DLVector2(float X, float Y) : X(X), Y(Y) { }

	inline DLVector2 DLVector2::Cross(const DLVector2& A, const DLVector2& B)
	{
		return { A.X * B.Y - B.X * A.Y };
	}

	inline float DLVector2::Dot(const DLVector2& A, const DLVector2& B)
	{
		return A.X * B.X + A.Y * B.Y;
	}

	inline float DLVector2::Length() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	inline bool DLVector2::Equals(const DLVector2& V) const
	{
		return std::abs(X - V.X) <= epsilon && std::abs(Y - V.Y) <= epsilon;
	}

	inline DLVector2 DLVector2::operator+(const DLVector2& V)
	{
		return { X + V.X, Y + V.Y };
	}

	inline DLVector2 DLVector2::operator-(const DLVector2& V)
	{
		return { X - V.X, Y - V.Y };
	}

	inline DLVector2 DLVector2::operator*(const DLVector2& V)
	{
		return { X * V.X, Y * V.Y };
	}

	inline DLVector2 DLVector2::operator/(const DLVector2& V)
	{
		return { X / V.X, Y / V.Y };
	}
}
