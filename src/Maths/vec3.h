// This file is a part of AtlasEngine
// CREATED : 04/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_VEC3__
#define __AE_VEC3__

#include <AEpch.h>

namespace AE::Maths
{
    /* ============================================================== Déclaration ============================================================== */

    // Prototypes
    template <class T>
    struct Vec3;
    template<typename T>
    std::ostream& operator<<(std::ostream&, const Vec3<T>&);

    // Classe
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

/* ============================================================== Définition ============================================================== */

    template <class T>
    Vec3<T>::Vec3()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    template <class T>
    Vec3<T>::Vec3(T x, T y, T z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    template <class T>
    Vec3<T>::Vec3(const Vec3<T> & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
    }

    template <class T>
    Vec3<T>::Vec3(const Vec3<T> & from, const Vec3<T> & to)
    {
        X = to.X - from.X;
        Y = to.Y - from.Y;
        Z = to.Z - from.Z;
    }

	template <class T>
	Vec3<T>::Vec3(std::initializer_list<T> args)
	{
		if(args.size() < 4)
		{
			switch(args.size())
			{
				case 1:
					X = *std::move(args.begin());
					Y = 0;
					Z = 0;
				break;

				case 2:		
					X = *std::move(args.begin());
					Y = *std::move(args.begin() + 1);
					Z = 0;
				break;

				case 3:
					X = *std::move(args.begin());
					Y = *std::move(args.begin() + 1);
					Z = *std::move(args.begin() + 2);
				break;

				default: break;
			}
		}
		else
			std::cout << "Vec3 initializer contains too much arguments" << std::endl;
	}

    template <class T>
    Vec3<T> & Vec3<T>::operator= (const Vec3<T> & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        return *this;
    }

    template <class T>
    bool Vec3<T>::operator== (const Vec3<T> & v)
    {
        if(X == v.X && Y == v.Y && Z == v.Z)
            return true;
        return false;
    }

    template <class T>
    bool Vec3<T>::operator!= (const Vec3<T> & v)
    {
        if(X != v.X && Y != v.Y && Z != v.Z)
            return true;
        return false;
    }



    template <class T>
    bool Vec3<T>::operator== (const T valeur)
    {
        if(X == valeur && Y == valeur && Z == valeur)
            return true;
        return false;
    }

    template <class T>
    bool Vec3<T>::operator!= (const T valeur)
    {
        if(X != valeur && Y != valeur && Z != valeur)
            return true;
        return false;
    }

    template <class T>
    Vec3<T> & Vec3<T>::operator+= (const Vec3<T> & v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator+ (const Vec3<T> & v) const
    {
        Vec3<T> t = *this;
        t += v;
        return t;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator+ (const T valeur)
    {
        X += valeur;
        Y += valeur;
        Z += valeur;

        return *this;
    }

    template <class T>
    Vec3<T> & Vec3<T>::operator-= (const Vec3<T> & v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator- (const Vec3<T> & v) const
    {
        Vec3<T> t = *this;
        t -= v;
        return t;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator- (const T valeur)
    {
        X -= valeur;
        Y -= valeur;
        Z -= valeur;

        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator- ()
    {
        X = -X;
        Y = -Y;
        Z = -Z;

        return *this;
    }

    template <class T>
    Vec3<T> & Vec3<T>::operator*= (const T a)
    {
        X *= a;
        Y *= a;
        Z *= a;
        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator* (const T a)const
    {
        Vec3<T> t = *this;
        t *= a;
        return t;
    }

    /*
     ######
    ##    ##   ##     ##
    ##         ##     ##
    ##       ###### ######
    ##         ##     ##
    ##    ##   ##     ##
     ######

    ░░░░░░░░░░░░▄▄░░░░░░░░░
    ░░░░░░░░░░░█░░█░░░░░░░░
    ░░░░░░░░░░░█░░█░░░░░░░░
    ░░░░░░░░░░█░░░█░░░░░░░░
    ░░░░░░░░░█░░░░█░░░░░░░░
    ███████▄▄█░░░░░██████▄░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█████░░░░░░░░░█░░
    ██████▀░░░░▀▀██████▀░░░
    */

    template <class T>
    Vec3<T> & Vec3<T>::operator* (const Vec3<T> &v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        return *this;
    }

    template <class T>
    Vec3<T> & Vec3<T>::operator/= (const T a)
    {
        X /= a;
        Y /= a;
        Z /= a;
        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::operator/ (const T a)const
    {
        Vec3<T> t = *this;
        t /= a;
        return t;
    }

    template <class T>
    bool Vec3<T>::operator< (const Vec3<T> &v)
    {
        if(X < v.X && Y < v.Y && Z < v.Z)
            return true;
        return false;
    }

    template <class T>
    bool Vec3<T>::operator< (const T valeur)
    {
        if(X < valeur && Y < valeur && Z < valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec3<T>::operator> (const Vec3<T> &v)
    {
        if(X > v.X && Y > v.Y && Z > v.Z)
            return true;
        return false;
    }
    template <class T>
    bool Vec3<T>::operator> (const T valeur)
    {
        if(X > valeur && Y > valeur && Z > valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec3<T>::operator<= (const Vec3<T> &v)
    {
        if(X <= v.X && Y <= v.Y && Z <= v.Z)
            return true;
        return false;
    }
    template <class T>
    bool Vec3<T>::operator<= (const T valeur)
    {
        if(X <= valeur && Y <= valeur && Z <= valeur)
            return true;
        return false;
    }




    template <class T>
    bool Vec3<T>::operator>= (const Vec3<T> &v)
    {
        if(X >= v.X && Y >= v.Y && Z >= v.Z)
            return true;
        return false;
    }
    template <class T>
    bool Vec3<T>::operator>= (const T valeur)
    {
        if(X >= valeur && Y >= valeur && Z >= valeur)
            return true;
        return false;
    }



    template <class T>
    Vec3<T> Vec3<T>::crossProduct(const Vec3<T> & v)const
    {
        Vec3<T> t;
        t.X = Y*v.Z - Z*v.Y;
        t.Y = Z*v.X - X*v.Z;
        t.Z = X*v.Y - Y*v.X;
        return t;
    }

    template <class T>
    double Vec3<T>::length()const
    {
        return sqrt(X*X + Y*Y + Z*Z);
    }

    template <class T>
    Vec3<T> & Vec3<T>::normalize()
    {
        (*this) /= length();
        return (*this);
    }

    template <class T>
    Vec3<T> Vec3<T>::COPY(const Vec3<T> &v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;

        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::DirectCopy()
    {
        Vec3<T> cop;
        cop.X = X;
        cop.Y = Y;
        cop.Z = Z;
        return cop;
    }

    template <class T>
    Vec3<T> Vec3<T>::SET(T x, T y, T z)
    {
        X = x;
        Y = y;
        Z = z;

        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::NEGATE()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        return *this;
    }

    template <class T>
    Vec3<T> Vec3<T>::NEGATEprecisely(bool x, bool y, bool z)
    {
        if(x) X = -X;
        if(y) Y = -Y;
        if(z) Z = -Z;

        return *this;
    }

    template <class T>
    double Vec3<T>::dot(Vec3<T> v)
    {
        return X * v.X + Y * v.Y + Z * v.Z;
    }

    template <class T>
    Vec3<T> Vec3<T>::absolute()
    {
        X = abs(X);
        Y = abs(Y);
        Z = abs(Z);

        return *this;
    }
}

#endif // __AE_VEC3__
