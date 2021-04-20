#pragma once

#include "Core/Common.h"
#include "Vector4.h"

namespace ScarletInterface { namespace Mathematics {

	struct Matrix4
	{
	public:
		union
		{
			float32 Elements[4 * 4];
			Vector4 Columns[4];
		};

		Matrix4();
		Matrix4(float32 Diagonal);

		Matrix4& Add(const Matrix4& _Other);
		Matrix4& Subtract(const Matrix4& _Other);
		Matrix4& Multiply(const Matrix4& _Other);
		Matrix4& Divide(const Matrix4& _Other);

		friend Matrix4& operator+(Matrix4 _Left, const Matrix4& _Right);
		friend Matrix4& operator-(Matrix4 _Left, const Matrix4& _Right);
		friend Matrix4& operator/(Matrix4 _Left, const Matrix4& _Right);
		friend Matrix4& operator*(Matrix4 _Left, const Matrix4& _Right);

		bool operator==(const Vector4& _Other);
		bool operator!=(const Vector4& _Other);

		Matrix4& operator+=(const Matrix4& _Other);
		Matrix4& operator-=(const Matrix4& _Other);
		Matrix4& operator*=(const Matrix4& _Other);
		Matrix4& operator/=(const Matrix4& _Other);

		String ToString() const;
	};

}}