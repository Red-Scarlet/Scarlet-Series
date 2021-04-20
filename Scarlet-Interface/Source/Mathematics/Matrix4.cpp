#include "Matrix4.h"
#include <sstream>

namespace ScarletInterface { namespace Mathematics {

	Matrix4::Matrix4()
	{
		for (uint32 i = 0; i < (4 * 4); i++)
			Elements[i] = 0.00f;
	}

	Matrix4::Matrix4(float32 Diagonal)
	{
		for (uint32 i = 0; i < (4 * 4); i++)
			Elements[i] = 0.0f;

		Elements[0 + 0 * 4] = Diagonal;
		Elements[1 + 1 * 4] = Diagonal;
		Elements[2 + 2 * 4] = Diagonal;
		Elements[3 + 3 * 4] = Diagonal;
	}

	Matrix4& Matrix4::Multiply(const Matrix4& Other)
	{
		float32 data[16];
		for (uint32 y = 0; y < 4; y++)
			for (uint32 x = 0; x < 4; x++) {
				float32 sum = 0.0f;
				for (uint32 e = 0; e < 4; e++)
					sum += Elements[x + e * 4] * Other.Elements[e + y * 4];
				data[x + y * 4] = sum;
			}
		memcpy(Elements, data, 4 * 4 * sizeof(float32));

		return *this;
	}

	Matrix4& Matrix4::Divide(const Matrix4& Other)
	{
		float32 data[16];
		for (uint32 y = 0; y < 4; y++)
			for (uint32 x = 0; x < 4; x++) {
				float32 sum = 0.0f;
				for (uint32 e = 0; e < 4; e++)
					sum += Elements[x + e * 4] / Other.Elements[e + y * 4];
				data[x + y * 4] = sum;
			}
		memcpy(Elements, data, 4 * 4 * sizeof(float32));

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& Other)
	{
		return Multiply(Other);
	}

	Matrix4& Matrix4::operator/=(const Matrix4& Other)
	{
		return Divide(Other);
	}

	Matrix4& operator/(Matrix4 Left, const Matrix4& Right)
	{
		return Left.Divide(Right);
	}

	Matrix4& operator*(Matrix4 Left, const Matrix4& Right)
	{
		return Left.Multiply(Right);
	}

	String Matrix4::ToString() const
	{
		std::stringstream result;
		result << "Matrix4: (" << Columns[0].x << ", " << Columns[1].x << ", " << Columns[2].x << ", " << Columns[3].x << "), ";
		result << "(" << Columns[0].y << ", " << Columns[1].y << ", " << Columns[2].y << ", " << Columns[3].y << "), ";
		result << "(" << Columns[0].z << ", " << Columns[1].z << ", " << Columns[2].z << ", " << Columns[3].z << "), ";
		result << "(" << Columns[0].w << ", " << Columns[1].w << ", " << Columns[2].w << ", " << Columns[3].w << ")";
		return result.str();
	}

}}