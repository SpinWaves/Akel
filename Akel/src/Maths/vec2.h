// This file is a part of Akel
// CREATED : 04/04/2021
// UPDATED : 03/06/2021

#ifndef __AK_VEC2__
#define __AK_VEC2__

#include <Akpch.h>

namespace Ak::Maths
{
    /* ============================================================== Déclaration ============================================================== */

    // Prototypes
    template <class T>
    struct Vec2;
    template<typename T>
    std::ostream& operator<<(std::ostream&, const Vec2<T>&);

    // Classe
    template <class T>
    struct Vec2
    {
        T X;
        T Y;

        Vec2();
        Vec2(T x, T y);
        Vec2(const Vec2 & v);
        Vec2(const Vec2 & from, const Vec2 & to);
		Vec2(std::initializer_list<T> args);

        Vec2 & operator= (const Vec2 & v);

        bool operator== (const Vec2 & v);
        bool operator!= (const Vec2 & v);

        bool operator== (const T valeur);
        bool operator!= (const T valeur);

        Vec2 & operator+= (const Vec2 & v);
        Vec2 operator+ (const Vec2 & v) const;
        Vec2 operator+ (const T valeur);

        Vec2 & operator-= (const Vec2 & v);
        Vec2 operator- (const Vec2 & v) const;
        Vec2 operator- (const T valeur);

        Vec2 & operator*= (const T a);
        Vec2 operator* (const T a)const;
        friend Vec2 operator* (const T a, const Vec2 & v)
		{
			return Vec2<T>(v.X*a, v.Y*a);
		}

        Vec2 & operator* (const Vec2 &v);

        Vec2 & operator/= (const T a);
        Vec2 operator/ (const T a)const;

        bool operator< (const Vec2 &v);
        bool operator< (const T valeur);

        bool operator> (const Vec2 &v);
        bool operator> (const T valeur);

        bool operator<= (const Vec2 &v);
        bool operator<= (const T valeur);

        bool operator>= (const Vec2 &v);
        bool operator>= (const T valeur);

        Vec2 crossProduct(const Vec2 & v)const;
        double length()const;
        Vec2 & normalize();

        Vec2 COPY(const Vec2 &v);
        Vec2 DirectCopy();

        Vec2 SET(T x, T y);

        friend std::ostream & operator<<(std::ostream& target, const Vec2& source)
		{
			target << source.X << ", " << source.Y;
			return target;
		}

        Vec2 NEGATE();
        Vec2 NEGATEprecisely(bool x, bool y);

        double dot(Vec2 v);
    };

    /* ============================================================== Définition ============================================================== */

    template <class T>
    Vec2<T>::Vec2()
    {
        X = 0;
        Y = 0;
    }

    template <class T>
    Vec2<T>::Vec2(T x, T y)
    {
        X = x;
        Y = y;
    }

    template <class T>
    Vec2<T>::Vec2(const Vec2<T> & v)
    {
        X = v.X;
        Y = v.Y;
    }

    template <class T>
    Vec2<T>::Vec2(const Vec2<T> & from, const Vec2<T> & to)
    {
        X = to.X - from.X;
        Y = to.Y - from.Y;
    }

	template <class T>
	Vec2<T>::Vec2(std::initializer_list<T> args)
	{
		if(args.size() < 3)
		{
			switch(args.size())
			{
				case 1:
					X = *std::move(args.begin());
					Y = 0;
				break;

				case 2:		
					X = *std::move(args.begin());
					Y = *std::move(args.begin() + 1);
				break;

				default: break;
			}
		}
		else
			std::cout << "Vec2 initializer contains too much arguments" << std::endl;
	}


    template <class T>
    Vec2<T> & Vec2<T>::operator= (const Vec2<T> & v)
    {
        X = v.X;
        Y = v.Y;
        return *this;
    }

    template <class T>
    bool Vec2<T>::operator== (const Vec2<T> & v)
    {
        if(X == v.X && Y == v.Y)
            return true;
        return false;
    }

    template <class T>
    bool Vec2<T>::operator!= (const Vec2<T> & v)
    {
        if(X != v.X && Y != v.Y)
            return true;
        return false;
    }



    template <class T>
    bool Vec2<T>::operator== (const T valeur)
    {
        if(X == valeur && Y == valeur)
            return true;
        return false;
    }

    template <class T>
    bool Vec2<T>::operator!= (const T valeur)
    {
        if(X != valeur && Y != valeur)
            return true;
        return false;
    }

    template <class T>
    Vec2<T> & Vec2<T>::operator+= (const Vec2<T> & v)
    {
        X += v.X;
        Y += v.Y;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator+ (const Vec2<T> & v) const
    {
        Vec2<T> t = *this;
        t += v;
        return t;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator+ (const T valeur)
    {
        X += valeur;
        Y += valeur;
        return *this;
    }

    template <class T>
    Vec2<T> & Vec2<T>::operator-= (const Vec2<T> & v)
    {
        X -= v.X;
        Y -= v.Y;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator- (const Vec2<T> & v) const
    {
        Vec2<T> t = *this;
        t -= v;
        return t;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator- (const T valeur)
    {
        X -= valeur;
        Y -= valeur;
        return *this;
    }

    template <class T>
    Vec2<T> & Vec2<T>::operator*= (const T a)
    {
        X *= a;
        Y *= a;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator* (const T a)const
    {
        Vec2<T> t = *this;
        t *= a;
        return t;
    }
    
    template <class T>
    Vec2<T> & Vec2<T>::operator* (const Vec2<T> &v)
    {
        X *= v.X;
        Y *= v.Y;
        return *this;
    }

    template <class T>
    Vec2<T> & Vec2<T>::operator/= (const T a)
    {
        X /= a;
        Y /= a;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::operator/ (const T a)const
    {
        Vec2<T> t = *this;
        t /= a;
        return t;
    }

    template <class T>
    bool Vec2<T>::operator< (const Vec2<T> &v)
    {
        if(X < v.X && Y < v.Y)
            return true;
        return false;
    }
    template <class T>
    bool Vec2<T>::operator< (const T valeur)
    {
        if(X < valeur && Y < valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec2<T>::operator> (const Vec2<T> &v)
    {
        if(X > v.X && Y > v.Y)
            return true;
        return false;
    }
    template <class T>
    bool Vec2<T>::operator> (const T valeur)
    {
        if(X > valeur && Y > valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec2<T>::operator<= (const Vec2<T> &v)
    {
        if(X <= v.X && Y <= v.Y)
            return true;
        return false;
    }
    template <class T>
    bool Vec2<T>::operator<= (const T valeur)
    {
        if(X <= valeur && Y <= valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec2<T>::operator>= (const Vec2<T> &v)
    {
        if(X >= v.X && Y >= v.Y)
            return true;
        return false;
    }
    template <class T>
    bool Vec2<T>::operator>= (const T valeur)
    {
        if(X >= valeur && Y >= valeur)
            return true;
        return false;
    }



    template <class T>
    Vec2<T> Vec2<T>::crossProduct(const Vec2<T> & v)const
    {
        return Vec2<T>(v.Y, -v.X);
    }

    template <class T>
    double Vec2<T>::length()const
    {
        return sqrt(X*X + Y*Y);
    }

    template <class T>
    Vec2<T> & Vec2<T>::normalize()
    {
        (*this) /= length();
        return (*this);
    }

    template <class T>
    Vec2<T> Vec2<T>::COPY(const Vec2<T> &v)
    {
        X = v.X;
        Y = v.Y;

        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::DirectCopy()
    {
        Vec2<T> cop;
        cop.X = X;
        cop.Y = Y;
        return cop;
    }

    template <class T>
    Vec2<T> Vec2<T>::SET(T x, T y)
    {
        X = x;
        Y = y;

        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::NEGATE()
    {
        X = -X;
        Y = -Y;
        return *this;
    }

    template <class T>
    Vec2<T> Vec2<T>::NEGATEprecisely(bool x, bool y)
    {
        if(x) X = -X;
        if(y) Y = -Y;

        return *this;
    }

    template <class T>
    double Vec2<T>::dot(Vec2<T> v)
    {
        return X * v.X + Y * v.Y;
    }
}

#endif // __AK_VEC2__
