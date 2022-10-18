#pragma once

#include "Vector3.h"

class Ray
{
public:
    Ray() 
    {

    }

    Ray(const Point3& origin, const Vector3& direction) : origin(origin), direction(direction)
    {
        
    }

    inline Point3 GetOrigin() const
    {
        return origin;
    }

    inline Vector3 GetDirection() const
    {
        return direction;
    }

    inline Point3 At(double t) const
    {
        return origin + direction * t;
    }

private:
    Point3 origin;
    Vector3 direction;
};