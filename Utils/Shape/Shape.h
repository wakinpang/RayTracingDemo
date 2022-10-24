#pragma once

#include "../Ray.h"

struct HitResult
{
    double Value;
    Point3 Point;
    Color Color;
    Vector3 Normal;
    bool OutSide;

    inline void SetSideNormal(Vector3 dir, Vector3 outNormal)
    {
        OutSide = Dot(dir, outNormal) < 0;
        Normal = OutSide ? outNormal : -outNormal;
    }
};

class Shape
{
public: 
    virtual bool Hit(Ray ray, double tMin, double tMax, HitResult& result) = 0;
    inline Vector3 GetPosition() const
    {
        return position;
    }

    inline void SetPosition(Vector3 pos)
    {
        position = pos; 
    }
    
protected:
    Vector3 position;
    Shape(Vector3 pos) : position(pos) // only an abstract class
    {

    }
};
