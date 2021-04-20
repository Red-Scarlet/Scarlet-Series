#pragma once

#include "Mathematics/Vector3.h"

namespace ScarletInterface { namespace Mathematics {

	struct Tensor3x3
	{
	public:
		Tensor3x3(const Mathematics::Vector3& _A = { 0.0f, 0.0f, 0.0f }, const Mathematics::Vector3& _B = { 0.0f, 0.0f, 0.0f },
			const Mathematics::Vector3& _C = { 0.0f, 0.0f, 0.0f })
			: A(_A), B(_B), C(_C)
		{
		}

	public:
		Mathematics::Vector3 A;
		Mathematics::Vector3 B;
		Mathematics::Vector3 C;
	};

}}