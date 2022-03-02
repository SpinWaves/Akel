// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 23/06/2021

#ifndef __AK_VEC3__
#define __AK_VEC3__

#include <Akpch.h>

namespace Ak::Maths
{
    template <class T>
    struct Vec3;
    template<typename T>
    std::ostream& operator<<(std::ostream&, const Vec3<T>&);

    template <class T>
    struct Vec3
    {
        T X;
        T Y;
        T Z;

        Vec3();
        Vec3(T x,T y,T z);
        Vec3(const Vec3 & v);
        Vec3(const Vec3 & from, const Vec3 & to);
		Vec3(std::initializer_list<T> args);

        Vec3 & operator= (const Vec3 & v);

        bool operator== (const Vec3 & v);
        bool operator!= (const Vec3 & v);

        bool operator== (const T valeur);
        bool operator!= (const T valeur);

        Vec3 & operator+= (const Vec3 & v);
        Vec3 operator+ (const Vec3 & v) const;
        Vec3 operator+ (const T valeur);

        Vec3 & operator-= (const Vec3 & v);
        Vec3 operator- (const Vec3 & v) const;
        Vec3 operator- (const T valeur);
        Vec3 operator- ();

        Vec3 & operator*= (const T a);
        Vec3 operator* (const T a)const;
        friend Vec3 operator* (const T a, const Vec3 & v)
		{
        	return Vec3<T>(v.X*a,v.Y*a,v.Z*a);
    	}
        Vec3 & operator* (const Vec3 &v);

        Vec3 & operator/= (const T a);
        Vec3 operator/ (const T a)const;

        bool operator< (const Vec3 &v);
        bool operator< (const T valeur);

        bool operator> (const Vec3 &v);
        bool operator> (const T valeur);

        bool operator<= (const Vec3 &v);
        bool operator<= (const T valeur);

        bool operator>= (const Vec3 &v);
        bool operator>= (const T valeur);

        Vec3 crossProduct(const Vec3 & v)const;
        double length()const;
        Vec3 & normalize();

        Vec3 COPY(const Vec3 &v);
        Vec3 DirectCopy();

        Vec3 SET(T x, T y, T z);

        friend std::ostream& operator<<(std::ostream& target, const Vec3& source)
		{
			target << source.X << ", " << source.Y << ", " << source.Z;
			return target;
		}

        Vec3 NEGATE();
        Vec3 NEGATEprecisely(bool x, bool y, bool z);

        double dot(Vec3 v);

        Vec3 absolute();
    };
}

#include <Maths/vec3.inl>

#endif // __AK_VEC3__
