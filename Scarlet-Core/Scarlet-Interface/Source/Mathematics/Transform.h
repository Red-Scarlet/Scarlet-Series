#pragma once

#include "Mathematics/Vector3.h"
#include "Mathematics/Matrix4.h"
#include "Mathematics/MathFunction.h"

namespace ScarletInterface { namespace Mathematics {

	struct Transform
	{
	public:
		Transform(const Vector3& _Translation = { 0.0f, 0.0f, 0.0f }, const Vector3& _Rotation = { 0.0f, 0.0f, 0.0f },
			const Vector3& _Scale = { 0.0f, 0.0f, 0.0f })
			: Translation(_Translation), Rotation(_Rotation), Scale(_Scale)
		{
		}

		Matrix4 GetTransform() const
		{
			return MathFunction::Translate(Translation) * Matrix4() * MathFunction::Scale(Scale);
		}

	public:
		Vector3 Translation = { 0.0f, 0.0f, 0.0f };
		Vector3 Rotation = { 0.0f, 0.0f, 0.0f };
		Vector3 Scale = { 1.0f, 1.0f, 1.0f };
	};

}}