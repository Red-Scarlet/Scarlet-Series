#include "Vector2.h"

namespace ScarletInterface { namespace Mathematics {

	Vector2::Vector2(const float32& _X, const float32& _Y)
		: x(_X), y(_Y)
	{
	}

	Vector2& Vector2::Add(const Vector2& Other)
	{
		x += Other.x;
		y += Other.y;

		return *this;
	}

	Vector2& Vector2::Subtract(const Vector2& Other)
	{
		x -= Other.x;
		y -= Other.y;

		return *this;
	}

	Vector2& Vector2::Multiply(const Vector2& Other)
	{
		x *= Other.x;
		y *= Other.y;

		return *this;
	}

	Vector2& Vector2::Divide(const Vector2& Other)
	{
		x /= Other.x;
		y /= Other.y;

		return *this;
	}

	Vector2& operator+(Vector2 Left, const Vector2& Right)
	{
		return Left.Add(Right);
	}

	Vector2& operator-(Vector2 Left, const Vector2& Right)
	{
		return Left.Subtract(Right);
	}

	Vector2& operator*(Vector2 Left, const Vector2& Right)
	{
		return Left.Multiply(Right);
	}

	Vector2& operator/(Vector2 Left, const Vector2& Right)
	{
		return Left.Divide(Right);
	}

	Vector2& Vector2::operator+=(const Vector2& Other)
	{
		return Add(Other);
	}

	Vector2& Vector2::operator-=(const Vector2& Other)
	{
		return Subtract(Other);
	}

	Vector2& Vector2::operator*=(const Vector2& Other)
	{
		return Multiply(Other);
	}

	Vector2& Vector2::operator/=(const Vector2& Other)
	{
		return Divide(Other);
	}

	String Vector2::ToString() const
	{
		return String("Vector2: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}

	bool Vector2::operator==(const Vector2& Other)
	{
		return x == Other.x && y == Other.y;
	}

	bool Vector2::operator!=(const Vector2& Other)
	{
		return !(*this == Other);
	}

}}