// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 10/03/2023

#include <Maths/vec4.h>

namespace Ak::Maths
{
    template <class T>
    Vec4<T>::Vec4(T x, T y, T z, T w) : X(std::move(x)), Y(std::move(y)), Z(std::move(z)), W(std::move(w)) {}

    template <class T>
    Vec4<T>::Vec4(const Vec4<T>& v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) {}

    template <class T>
    Vec4<T>::Vec4(const Vec4 & from, const Vec4<T>& to)
    {
        X = to.X - from.X;
        Y = to.Y - from.Y;
        Z = to.Z - from.Z;
        W = to.W - from.W;
    }

    template <class T>
    Vec4<T>& Vec4<T>::operator= (const Vec4<T>& v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
        return *this;
    }

    template <class T>
    bool Vec4<T>::operator== (const Vec4<T>& v)
    {
        return X == v.X && Y == v.Y && Z == v.Z && W == v.W;
    }
    
	template <class T>
    bool Vec4<T>::operator!= (const Vec4<T>& v)
    {
        return X != v.X && Y != v.Y && Z != v.Z && W != v.W;
    }

    template <class T>
    bool Vec4<T>::operator== (const T value)
    {
        return X == value && Y == value && Z == value && W == value;
    }

    template <class T>
    bool Vec4<T>::operator!= (const T value)
    {
        return X != value && Y != value && Z != value && W != value;
    }
    
	template <class T>
    Vec4<T>& Vec4<T>::operator+= (const Vec4<T>& v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        W += v.W;
        return *this;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator+ (const Vec4<T>& v) const
    {
        Vec4 t = *this;
        t += v;
        return t;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator+ (const T value)
    {
        X += value;
        Y += value;
        Z += value;
        W += value;
        return *this;
    }
    
	template <class T>
    Vec4<T>& Vec4<T>::operator-= (const Vec4<T>& v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        W -= v.W;
        return *this;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator- (const Vec4<T>& v) const
    {
        Vec4 t = *this;
        t -= v;
        return t;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator- (const T value)
    {
        X -= value;
        Y -= value;
        Z -= value;
        W -= value;
        return *this;
    }
    
	template <class T>
    Vec4<T>& Vec4<T>::operator*= (const T a)
    {
        X *= a;
        Y *= a;
        Z *= a;
        W *= a;
        return *this;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator* (const T a)const
    {
        Vec4 t = *this;
        t *= a;
        return t;
    }
    
	template <class T>
    Vec4<T>& Vec4<T>::operator* (const Vec4<T>&v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        W *= v.W;
        return *this;
    }
    
	template <class T>
    Vec4<T>& Vec4<T>::operator/= (const T a)
    {
        X /= a;
        Y /= a;
        Z /= a;
        W /= a;
        return *this;
    }
    
	template <class T>
    Vec4<T> Vec4<T>::operator/ (const T a)const
    {
        Vec4 t = *this;
        t /= a;
        return t;
    }
    
	template <class T>
    bool Vec4<T>::operator< (const Vec4<T>&v)
    {
        if(X < v.X && Y < v.Y && Z < v.Z && W < v.W)
            return true;
        return false;
    }
    
	template <class T>
    bool Vec4<T>::operator< (const T value)
    {
        if(X < value && Y < value && Z < value && W < value)
            return true;
        return false;
    }

    template <class T>
    bool Vec4<T>::operator> (const Vec4<T>&v)
    {
        return X > v.X && Y > v.Y && Z > v.Z && W > v.W;
    }

	template <class T>
    bool Vec4<T>::operator> (const T value)
    {
        return X > value && Y > value && Z > value && W > value;
    }

    template <class T>
    bool Vec4<T>::operator<= (const Vec4<T>&v)
    {
        return X <= v.X && Y <= v.Y && Z <= v.Z && W <= v.W;
    }

    template <class T>
    bool Vec4<T>::operator<= (const T value)
    {
        return X <= value && Y <= value && Z <= value && W <= value;
    }

    template <class T>
    bool Vec4<T>::operator>= (const Vec4<T>&v)
    {
        return X >= v.X && Y >= v.Y && Z >= v.Z && W >= v.W;
    }

    template <class T>
    bool Vec4<T>::operator>= (const T value)
    {
        return X >= value && Y >= value && Z >= value && W >= value;
    }

    template <class T>
    Vec4<T> Vec4<T>::crossProduct(const Vec4<T>& v)const
    {
        Vec4<T> t;
        t.X = Y*v.Z - Z*v.Y;
        t.Y = Z*v.X - X*v.Z;
        t.Z = X*v.Y - Y*v.X;
        t.W = 1;
        return t;
    }

    template <class T>
    double Vec4<T>::length()const
    {
        return sqrt(X*X + Y*Y + Z*Z + W*W);
    }
    
	template <class T>
    void Vec4<T>::normalize()
    {
        (*this) /= length();
    }
    
	template <class T>
    Vec4<T> Vec4<T>::copy()
    {
        Vec4<T> cop;
        cop.X = X;
        cop.Y = Y;
        cop.Z = Z;
        cop.W = W;
        return cop;
    }
    
	template <class T>
    void Vec4<T>::set(T x, T y, T z, T w)
    {
        X = std::move(x);
        Y = std::move(y);
        Z = std::move(z);
        W = std::move(w);
    }
    
	template <class T>
	void Vec4<T>::negate()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        W = -W;
    }
    
	template <class T>
    void Vec4<T>::negatePrecisely(bool x, bool y, bool z, bool w)
    {
        if(x) X = -X;
        if(y) Y = -Y;
        if(z) Z = -Z;
        if(w) W = -W;
    }
    
	template <class T>
    double Vec4<T>::dot(Vec4<T> v)
    {
        return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
    }
}

