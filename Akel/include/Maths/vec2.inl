// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 10/03/2023

#include <Maths/vec2.h>

namespace Ak::Maths
{
	template <class T>
	Vec2<T>::Vec2(T x, T y) : X(std::move(x)), Y(std::move(y)) {}

	template <class T>
	Vec2<T>::Vec2(const Vec2<T>& v) : X(v.X), Y(v.Y) {}

	template <class T>
	Vec2<T>::Vec2(const Vec2<T>& from, const Vec2<T>& to)
	{
		X = to.X - from.X;
		Y = to.Y - from.Y;
	}

    template <class T>
    Vec2<T>& Vec2<T>::operator= (const Vec2<T>& v)
    {
        X = v.X;
        Y = v.Y;
        return *this;
    }

    template <class T>
    bool Vec2<T>::operator== (const Vec2<T>& v)
    {
        return X == v.X && Y == v.Y;
    }

    template <class T>
    bool Vec2<T>::operator!= (const Vec2<T>& v)
    {
        return X != v.X && Y != v.Y;
    }

    template <class T>
    bool Vec2<T>::operator== (const T value)
    {
        return X == value && Y == value;
    }

    template <class T>
    bool Vec2<T>::operator!= (const T value)
    {
        return X != value && Y != value;
    }

    template <class T>
    Vec2<T>&  Vec2<T>::operator+= (const Vec2<T>& v)
    {
        X += v.X;
        Y += v.Y;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator+ (const Vec2<T>& v) const
    {
        Vec2<T> t = *this;
        t += v;
        return t;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator+ (const T value)
    {
        X += value;
        Y += value;
        return *this;
    }

    template <class T>
    Vec2<T>&  Vec2<T>::operator-= (const Vec2<T>& v)
    {
        X -= v.X;
        Y -= v.Y;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator- (const Vec2<T>& v) const
    {
        Vec2<T> t = *this;
        t -= v;
        return t;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator- (const T value)
    {
        X -= value;
        Y -= value;
        return *this;
    }

    template <class T>
    Vec2<T>&  Vec2<T>::operator*= (const T a)
    {
        X *= a;
        Y *= a;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator* (const T a) const
    {
        Vec2<T> t = *this;
        t *= a;
        return t;
    }
    
    template <class T>
    Vec2<T>& Vec2<T>::operator* (const Vec2<T>& v)
    {
        X *= v.X;
        Y *= v.Y;
        return *this;
    }

    template <class T>
    Vec2<T>& Vec2<T>::operator/= (const T a)
    {
        X /= a;
        Y /= a;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator/ (const T a) const
    {
        Vec2<T> t = *this;
        t /= a;
        return t;
    }

    template <class T>
    bool Vec2<T>::operator< (const Vec2<T>& v)
    {
        return X < v.X && Y < v.Y;
    }

    template <class T>
    bool Vec2<T>::operator< (const T value)
    {
        return X < value && Y < value;
    }

    template <class T>
    bool Vec2<T>::operator> (const Vec2<T>& v)
    {
        return X > v.X && Y > v.Y;
    }

    template <class T>
    bool Vec2<T>::operator> (const T value)
    {
        return X > value && Y > value;
    }

    template <class T>
    bool Vec2<T>::operator<= (const Vec2<T>& v)
    {
        return X <= v.X && Y <= v.Y;
    }

    template <class T>
    bool Vec2<T>::operator<= (const T value)
    {
        return X <= value && Y <= value;
    }

    template <class T>
    bool Vec2<T>::operator>= (const Vec2<T>& v)
    {
        return X >= v.X && Y >= v.Y;
    }

    template <class T>
    bool Vec2<T>::operator>= (const T value)
    {
        return X >= value && Y >= value;
    }

    template <class T>
    Vec2<T> Vec2<T>::crossProduct(const Vec2<T>&  v) const
    {
        return Vec2<T>(v.Y, -v.X);
    }

    template <class T>
    double Vec2<T>::length() const
    {
        return sqrt(X*X + Y*Y);
    }

    template <class T>
    void Vec2<T>::normalize()
    {
        (*this) /= length();
    }

    template <class T>
    Vec2<T> Vec2<T>::copy()
    {
        Vec2<T> cop;
        cop.X = X;
        cop.Y = Y;
        return cop;
    }

    template <class T>
    void Vec2<T>::set(T x, T y)
    {
        X = x;
        Y = y;
    }

    template <class T>
    void Vec2<T>::negate()
    {
        X = -X;
        Y = -Y;
    }

    template <class T>
    void Vec2<T>::negatePrecisely(bool x, bool y)
    {
        if(x) X = -X;
        if(y) Y = -Y;
    }

    template <class T>
    double Vec2<T>::dot(const Vec2<T>& v)
    {
        return X * v.X + Y * v.Y;
    }
}

