#pragma once

#include <cmath>


namespace DontLaugh
{
	/* 3D Vector implemented by DontLaugh */
	struct DLVector3
	{
	public:
		float X;
		float Y;
		float Z;

	public:
		DLVector3();
		DLVector3(float InF);
		DLVector3(float X, float Y, float Z);

		static const DLVector3 Zero;
		static const DLVector3 One;

		static DLVector3 Cross(const DLVector3& A, const DLVector3& B);
		static float Dot(const DLVector3& A, const DLVector3& B);

		float Length() const;
		bool Equals(const DLVector3& V) const;

		DLVector3 operator+(const DLVector3& V);
		DLVector3 operator-(const DLVector3& V);
		DLVector3 operator*(const DLVector3& V);
		DLVector3 operator/(const DLVector3& V);

	private:
		static const float epsilon;
	};


	const DLVector3 DLVector3::Zero(0, 0, 0);
	const DLVector3 DLVector3::One(1, 1, 1);
	constexpr float DLVector3::epsilon = 1e-4f;

	inline DLVector3::DLVector3() : X(0), Y(0), Z(0) { }

	inline DLVector3::DLVector3(float InF) : X(InF), Y(InF), Z(InF) { }

	inline DLVector3::DLVector3(float X, float Y, float Z) : X(X), Y(Y), Z(Z) { }

	inline DLVector3 DLVector3::Cross(const DLVector3& A, const DLVector3& B)
	{
		return { A.Y * B.Z - A.Z * B.Y, A.Z * B.X - A.X * B.Z, A.X * B.Y - A.Y * B.X };
	}

	inline float DLVector3::Dot(const DLVector3& A, const DLVector3& B)
	{
		return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
	}

	inline float DLVector3::Length() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z);
	}

	inline bool DLVector3::Equals(const DLVector3& V) const
	{
		return std::abs(X - V.X) <= epsilon && std::abs(Y - V.Y) <= epsilon && std::abs(Z - V.Z) <= epsilon;
	}

	inline DLVector3 DLVector3::operator+(const DLVector3& V)
	{
		return { X + V.X, Y + V.Y, Z + V.Z };
	}

	inline DLVector3 DLVector3::operator-(const DLVector3& V)
	{
		return { X - V.X, Y - V.Y, Z - V.Z };
	}

	inline DLVector3 DLVector3::operator*(const DLVector3& V)
	{
		return { X * V.X, Y * V.Y, Z * V.Z };
	}

	inline DLVector3 DLVector3::operator/(const DLVector3& V)
	{
		return { X / V.X, Y / V.Y, Z / V.Z };
	}
}
