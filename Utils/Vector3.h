#pragma once

#include <cmath>
#include <iostream>

class Vector3
{
public:
    // constructors
    Vector3() : e {0, 0, 0}
    {

    }

    Vector3(double x, double y, double z)
    {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    // base property
    inline double GetX() const
    {
        return e[0];
    }

    inline double GetY() const
    {
        return e[1];
    }

    inline double GetZ() const
    {
        return e[2];
    }

    inline void SetX(double v)
    {
        e[0] = v;
        return;
    }

    inline void SetY(double v) 
    {
        e[1] = v;
        return;
    }

    inline void SetZ(double v) 
    {
        e[2] = v;
        return;
    }

    // operator
    inline Vector3 operator-() const
    {
        return Vector3(-e[0], -e[1], -e[2]);
    }

    inline Vector3& operator+=(const Vector3& t)
    {
        e[0] += t.GetX();
        e[1] += t.GetY();
        e[2] += t.GetZ();

        return *this;
    }

    inline Vector3& operator*=(const double& t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    inline Vector3& operator/=(const double& t)
    {
        return *this *= (1 / t);
    }

    inline Vector3 operator+(const Vector3& t) const
    {
        return Vector3(e[0] + t.GetX(), e[1] + t.GetY(), e[2] + t.GetZ());
    }

    inline Vector3 operator-(const Vector3& t) const
    {
        return Vector3(e[0] - t.GetX(), e[1] - t.GetY(), e[2] - t.GetZ());
    }

    inline Vector3 operator*(const double t) const
    {
        return Vector3(e[0] * t, e[1] * t, e[2] * t);
    }

    inline Vector3 operator/(const double t) const
    {
        return *this * (1 / t);
    }

    // Length
    inline double Length() const
    {
        return std::sqrt(LengthSquare());
    }

    inline double LengthSquare() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
private:
    double e[3];
};

// Utility functions for Vector3

inline Vector3 operator*(double v, const Vector3& t) // reverse condition in operator *
{
    return t * v;
}

inline double Dot(const Vector3& u, const Vector3& v)
{
    return u.GetX() * v.GetX() + u.GetY() * v.GetY() + u.GetZ() + v.GetZ();
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
    return Vector3(u.GetY() * v.GetZ() - u.GetZ() * v.GetY(), 
                   u.GetZ() * v.GetX() - u.GetX() * v.GetZ(),
                   u.GetX() * v.GetY() - u.GetY() * v.GetX());
}

inline Vector3 Normalize(const Vector3& v)
{
    return v / v.Length();
}

inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << v.GetX() << ' ' << v.GetY() << ' ' << v.GetZ();
}

// Name reference
using Color = Vector3;
using Point3 = Vector3;