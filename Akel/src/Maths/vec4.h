// This file is a part of Akel
// Author : @kbz_8
// CREATED : 04/04/2021
// UPDATED : 03/06/2021

#ifndef __AK_VEC4__
#define __AK_VEC4__

#include <Akpch.h>

namespace Ak::Maths
{
    template <class T>
    struct Vec4;
    template<typename T>
    std::ostream& operator<<(std::ostream&, const Vec4<T>&);

    template <class T>
    struct Vec4
    {
        T X;
        T Y;
        T Z;
        T W;

        Vec4();
        Vec4(T x,T y,T z, T w);
        Vec4(const Vec4 & v);
        Vec4(const Vec4 & from, const Vec4 & to);
		Vec4(std::initializer_list<T> args);

        Vec4 & operator= (const Vec4 & v);

        bool operator== (const Vec4 & v);
        bool operator!= (const Vec4 & v);

        bool operator== (const T valeur);
        bool operator!= (const T valeur);

        Vec4 & operator+= (const Vec4 & v);
        Vec4 operator+ (const Vec4 & v) const;
        Vec4 operator+ (const T valeur);

        Vec4 & operator-= (const Vec4 & v);
        Vec4 operator- (const Vec4 & v) const;
        Vec4 operator- (const T valeur);

        Vec4 & operator*= (const T a);
        Vec4 operator* (const T a)const;
        friend Vec4 operator* (const T a,const Vec4 & v)
		{
			return Vec4<T>(v.X*a, v.Y*a, v.Z*a, v.W*a);
		}

        Vec4 & operator* (const Vec4 &v);

        Vec4 & operator/= (const T a);
        Vec4 operator/ (const T a)const;

        bool operator< (const Vec4 &v);
        bool operator< (const T valeur);

        bool operator> (const Vec4 &v);
        bool operator> (const T valeur);

        bool operator<= (const Vec4 &v);
        bool operator<= (const T valeur);

        bool operator>= (const Vec4 &v);
        bool operator>= (const T valeur);

        Vec4 crossProduct(const Vec4 & v)const;
        double length()const;
        Vec4 & normalize();

        Vec4 COPY(const Vec4 &v);
        Vec4 DirectCopy();

        Vec4 SET(T x, T y, T z, T w);

        friend std::ostream& operator<<(std::ostream& target, const Vec4& source)
		{
        	return target << source.X << ", " << source.Y << ", " << source.Z << ", " << source.W;
    	}


        Vec4 NEGATE();
        Vec4 NEGATEprecisely(bool x, bool y, bool z, bool w);

        double dot(Vec4 v);
    };
}

#include <Maths/vec4.inl>

#endif // __AK_VEC4__

