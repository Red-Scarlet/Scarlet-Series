#pragma once

#include "Core/Common.h"

namespace ScarletInterface { namespace Mathematics {

	struct Vector2
	{
	public:
		float32 x = 0, y = 0;

		Vector2() = default;
		Vector2(const float32& _X, const float32& _Y);

		Vector2& Add(const Vector2& other);
		Vector2& Subtract(const Vector2& other);
		Vector2& Multiply(const Vector2& other);
		Vector2& Divide(const Vector2& other);

		friend Vector2& operator+(Vector2 Left, const Vector2& Right);
		friend Vector2& operator-(Vector2 Left, const Vector2& Right);
		friend Vector2& operator/(Vector2 Left, const Vector2& Right);
		friend Vector2& operator*(Vector2 Left, const Vector2& Right);

		bool operator==(const Vector2& Other);
		bool operator!=(const Vector2& Other);

		Vector2& operator+=(const Vector2& Other);
		Vector2& operator-=(const Vector2& Other);
		Vector2& operator*=(const Vector2& Other);
		Vector2& operator/=(const Vector2& Other);

		String ToString() const;
	};

}}