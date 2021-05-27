#pragma once

#include "Core/Common.h"

namespace ScarletInterface { namespace Mathematics {

	struct Vector4
	{
	public:
		float32 x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

		Vector4() = default;
		Vector4(const float32& _X, const float32& _Y, const float32& _Z, const float32& _W);

		Vector4& Add(const Vector4& Other);
		Vector4& Subtract(const Vector4& Other);
		Vector4& Multiply(const Vector4& Other);
		Vector4& Divide(const Vector4& Other);

		friend Vector4& operator+(Vector4 Left, const Vector4& Right);
		friend Vector4& operator-(Vector4 Left, const Vector4& Right);
		friend Vector4& operator/(Vector4 Left, const Vector4& Right);
		friend Vector4& operator*(Vector4 Left, const Vector4& Right);

		bool operator==(const Vector4& Other);
		bool operator!=(const Vector4& Other);

		Vector4& operator+=(const Vector4& Other);
		Vector4& operator-=(const Vector4& Other);
		Vector4& operator*=(const Vector4& Other);
		Vector4& operator/=(const Vector4& Other);

		String ToString() const;
	};

}}