#include "Vector4.h"

namespace ScarletInterface { namespace Mathematics {

	Vector4::Vector4(const float32& _X, const float32& _Y, const float32& _Z, const float32& _W)
		: x(_X), y(_Y), z(_Z), w(_W)
	{
	}

	Vector4& Vector4::Add(const Vector4& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;
		w += Other.w;

		return *this;
	}

	Vector4& Vector4::Subtract(const Vector4& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;
		w -= Other.w;

		return *this;
	}

	Vector4& Vector4::Multiply(const Vector4& Other)
	{
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;
		w *= Other.w;

		return *this;
	}

	Vector4& Vector4::Divide(const Vector4& Other)
	{
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;
		w /= Other.w;

		return *this;
	}

	bool Vector4::operator==(const Vector4& Other)
	{
		return x == Other.x && y == Other.y && z == Other.z && w == Other.w;
	}

	bool Vector4::operator!=(const Vector4& Other)
	{
		return !(*this == Other);
	}

	Vector4& Vector4::operator+=(const Vector4& Other)
	{
		return Add(Other);
	}

	Vector4& Vector4::operator-=(const Vector4& Other)
	{
		return Subtract(Other);
	}

	Vector4& Vector4::operator*=(const Vector4& Other)
	{
		return Multiply(Other);
	}

	Vector4& Vector4::operator/=(const Vector4& Other)
	{
		return Divide(Other);
	}

	String Vector4::ToString() const
	{
		return String("Vector4: (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")");
	}

	Vector4& operator+(Vector4 Left, const Vector4& Right)
	{
		return Left.Add(Right);
	}

	Vector4& operator-(Vector4 Left, const Vector4& Right)
	{
		return Left.Subtract(Right);
	}

	Vector4& operator*(Vector4 Left, const Vector4& Right)
	{
		return Left.Multiply(Right);
	}

	Vector4& operator/(Vector4 Left, const Vector4& Right)
	{
		return Left.Divide(Right);
	}

}}