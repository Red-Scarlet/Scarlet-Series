#include "Vector3.h"

namespace ScarletInterface { namespace Mathematics {

	Vector3::Vector3(const float32& _X, const float32& _Y, const float32& _Z)
		: x(_X), y(_Y), z(_Z)
	{
	}

	Vector3& Vector3::Add(const Vector3& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;

		return *this;
	}

	Vector3& Vector3::Subtract(const Vector3& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;

		return *this;
	}

	Vector3& Vector3::Multiply(const Vector3& Other)
	{
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;

		return *this;
	}

	Vector3& Vector3::Divide(const Vector3& Other)
	{
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;

		return *this;
	}

	bool Vector3::operator==(const Vector3& Other)
	{
		return x == Other.x && y == Other.y && z == Other.z;
	}

	bool Vector3::operator!=(const Vector3& Other)
	{
		return !(*this == Other);
	}

	Vector3& Vector3::operator+=(const Vector3& Other)
	{
		return Add(Other);
	}

	Vector3& Vector3::operator-=(const Vector3& Other)
	{
		return Subtract(Other);
	}

	Vector3& Vector3::operator*=(const Vector3& Other)
	{
		return Multiply(Other);
	}

	Vector3& Vector3::operator/=(const Vector3& Other)
	{
		return Divide(Other);
	}

	String Vector3::ToString() const
	{
		return String("Vector3: (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}

	Vector3& operator+(Vector3 Left, const Vector3& Right)
	{
		return Left.Add(Right);
	}

	Vector3& operator-(Vector3 Left, const Vector3& Right)
	{
		return Left.Subtract(Right);
	}

	Vector3& operator*(Vector3 Left, const Vector3& Right)
	{
		return Left.Multiply(Right);
	}

	Vector3& operator*(Vector3 Left, const float32& Right)
	{
		return Left.Multiply(Vector3(Right, Right, Right));
	}

	Vector3& operator/(Vector3 Left, const Vector3& Right)
	{
		return Left.Divide(Right);
	}

}}