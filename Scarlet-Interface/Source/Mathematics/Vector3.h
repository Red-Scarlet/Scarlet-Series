#pragma once

#include "Core/Common.h"

namespace ScarletInterface { namespace Mathematics {

	struct Vector3
	{
	public:
		float32 x = 0.0f, y = 0.0f, z = 0.0f;

		Vector3() = default;
		Vector3(const float32& _X, const float32& _Y, const float32& _Z);

		Vector3& Add(const Vector3& other);
		Vector3& Subtract(const Vector3& other);
		Vector3& Multiply(const Vector3& other);
		Vector3& Divide(const Vector3& other);

		friend Vector3& operator+(Vector3 Left, const Vector3& Right);
		friend Vector3& operator-(Vector3 Left, const Vector3& Right);
		friend Vector3& operator/(Vector3 Left, const Vector3& Right);
		friend Vector3& operator*(Vector3 Left, const Vector3& Right);
		friend Vector3& operator*(Vector3 Left, const float32& Right);

		bool operator==(const Vector3& Other);
		bool operator!=(const Vector3& Other);

		Vector3& operator+=(const Vector3& Other);
		Vector3& operator-=(const Vector3& Other);
		Vector3& operator*=(const Vector3& Other);
		Vector3& operator/=(const Vector3& Other);

		String ToString() const;
	};

}}