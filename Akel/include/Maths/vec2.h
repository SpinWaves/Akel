// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 09/03/2023

#ifndef __AK_VEC2__
#define __AK_VEC2__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak::Maths
{
	template <class T>
	struct Vec2
	{
		T X;
		T Y;

		Vec2() = default;
		Vec2(T x, T y);
		Vec2(const Vec2& v);
		Vec2(const Vec2& from, const Vec2& to);

		Vec2 & operator= (const Vec2& v);

		bool operator== (const Vec2& v);
		bool operator!= (const Vec2& v);

		bool operator== (const T value);
		bool operator!= (const T value);

		Vec2& operator+= (const Vec2& v);
		Vec2 operator+ (const Vec2& v) const;
		Vec2 operator+ (const T value);

		Vec2& operator-= (const Vec2& v);
		Vec2 operator- (const Vec2& v) const;
		Vec2 operator- (const T value);

		Vec2& operator*= (const T a);
		Vec2 operator* (const T a) const;
		Vec2 operator* (const T a, const Vec2& v) { return Vec2<T>(v.X * a, v.Y * a); }

		Vec2& operator* (const Vec2& v);

		Vec2& operator/= (const T a);
		Vec2 operator/ (const T a) const;

		bool operator< (const Vec2& v);
		bool operator< (const T value);

		bool operator> (const Vec2& v);
		bool operator> (const T value);

		bool operator<= (const Vec2& v);
		bool operator<= (const T value);

		bool operator>= (const Vec2& v);
		bool operator>= (const T value);

		Vec2 crossProduct(const Vec2& v) const;
		double length() const;
		Vec2& normalize();

		Vec2 copy();

		Vec2 set(T x, T y);

		Vec2 negate();
		Vec2 negatePrecisely(bool x, bool y);

		double dot(Vec2 v);
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int32_t>;
	using Vec2ui = Vec2<uint32_t>;
}


#include <Maths/vec2.inl>

#endif // __AK_VEC2__
