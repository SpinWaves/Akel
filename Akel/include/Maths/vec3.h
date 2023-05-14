// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 14/05/2023

#ifndef __AK_VEC3__
#define __AK_VEC3__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak::Maths
{
	template <class T>
	struct Vec3
	{
		T X;
		T Y;
		T Z;

		Vec3() = default;
		Vec3(T x,T y,T z);
		Vec3(const Vec3& v);
		Vec3(const Vec3& from, const Vec3& to);

		Vec3& operator= (const Vec3& v);

		bool operator== (const Vec3& v);
		bool operator!= (const Vec3& v);

		bool operator== (const T value);
		bool operator!= (const T value);

		Vec3& operator+= (const Vec3& v);
		Vec3 operator+ (const Vec3& v) const;
		Vec3 operator+ (const T value);

		Vec3& operator-= (const Vec3& v);
		Vec3 operator- (const Vec3& v) const;
		Vec3 operator- (const T value);
		Vec3 operator- ();

		Vec3& operator*= (const T a);
		Vec3 operator* (const T a) const;
		friend Vec3 operator* (const T a, const Vec3& v) { return Vec3<T>(v.X * a,v.Y * a,v.Z * a); }
		Vec3& operator* (const Vec3& v);

		Vec3& operator/= (const T a);
		Vec3 operator/ (const T a) const;

		bool operator< (const Vec3& v);
		bool operator< (const T value);

		bool operator> (const Vec3& v);
		bool operator> (const T value);

		bool operator<= (const Vec3& v);
		bool operator<= (const T value);

		bool operator>= (const Vec3& v);
		bool operator>= (const T value);

		Vec3 crossProduct(const Vec3& v) const;
		double length() const;
		void normalize();

		Vec3 copy();
		void set(T x, T y, T z);
		void negate();
		void negatePrecisely(bool x, bool y, bool z);
		double dot(Vec3 v);
		void absolute();
	};

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int32_t>;
	using Vec3ui = Vec3<uint32_t>;
}

namespace Ak
{
	using Vec3f = Maths::Vec3<float>;
	using Vec3d = Maths::Vec3<double>;
	using Vec3i = Maths::Vec3<int32_t>;
	using Vec3ui = Maths::Vec3<uint32_t>;
}

#include <Maths/vec3.inl>

#endif // __AK_VEC3__
