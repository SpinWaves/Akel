// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 14/05/2023

#ifndef __AK_VEC4__
#define __AK_VEC4__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak::Maths
{
    template <class T>
    struct Vec4
	{
		T X;
		T Y;
		T Z;
		T W;

		Vec4() = default;
		Vec4(T x,T y,T z, T w);
		Vec4(const Vec4& v);
		Vec4(const Vec4& from, const Vec4& to);

		Vec4& operator= (const Vec4& v);

		bool operator== (const Vec4& v);
		bool operator!= (const Vec4& v);

		bool operator== (const T value);
		bool operator!= (const T value);

		Vec4& operator+= (const Vec4& v);
		Vec4 operator+ (const Vec4& v) const;
		Vec4 operator+ (const T value);

		Vec4& operator-= (const Vec4& v);
		Vec4 operator- (const Vec4& v) const;
		Vec4 operator- (const T value);

		Vec4& operator*= (const T a);
		Vec4 operator* (const T a) const;
		friend Vec4 operator* (const T a, const Vec4& v) { return Vec4<T>(v.X * a, v.Y * a, v.Z * a, v.W * a); }

		Vec4& operator* (const Vec4&v);

		Vec4& operator/= (const T a);
		Vec4 operator/ (const T a) const;

		bool operator< (const Vec4&v);
		bool operator< (const T value);

		bool operator> (const Vec4&v);
		bool operator> (const T value);

		bool operator<= (const Vec4&v);
		bool operator<= (const T value);

		bool operator>= (const Vec4&v);
		bool operator>= (const T value);

		Vec4 crossProduct(const Vec4& v)const;
		double length()const;
		void normalize();

		Vec4 copy();

		void set(T x, T y, T z, T w);

		void negate();
		void negatePrecisely(bool x, bool y, bool z, bool w);

		double dot(Vec4 v);
	};

    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
    using Vec4i = Vec4<int32_t>;
    using Vec4ui = Vec4<uint32_t>;
}

namespace Ak
{
	using Vec4f = Maths::Vec4<float>;
	using Vec4d = Maths::Vec4<double>;
	using Vec4i = Maths::Vec4<int32_t>;
	using Vec4ui = Maths::Vec4<uint32_t>;
}

#include <Maths/vec4.inl>

#endif // __AK_VEC4__

