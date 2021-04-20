#pragma once

#include "Vector3.h"
#include "Matrix4.h"

namespace ScarletInterface { namespace Mathematics {

	struct MathFunction
	{
	public:
		static Matrix4 Orthographic(const float32& _Left, const float32& _Right, const float32& _Bottom, const float32& _Top, const float32& _Near, const float32& _Far);
		static Matrix4 Perspective(const float32& _FOV, const float32& _AspectRatio, const float32& _Near, const float32& _Far);
		static Matrix4 LookAt(const Vector3& _Camera, const Vector3& _Object, const Vector3& _Up);
		static Matrix4 Translate(const Vector3& _Translation);
		static Matrix4 Rotation(const Vector3& _Rotate);
		static Matrix4 Scale(const Vector3& _Scale);
		static Matrix4 Inverse(const Matrix4& _Matrix);

		static float32* ValuePtr(const Matrix4& _Matrix);

	};

}}