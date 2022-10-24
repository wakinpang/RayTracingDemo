#pragma once

#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
    Camera(Point3 position, double width, double height, double focus);
    Ray GetRay(double u, double v);

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    double width;
    double height;
    double focus;
    Vector3 horizontal;
    Vector3 vertical;
};