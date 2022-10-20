#pragma once

#include "Shape.h"

class Sphere : Shape
{
public:
    Sphere(Vector3 pos, double radius);
    bool Hit(Ray ray, double tMin, double tMax, HitResult& result) override;

private:
    double radius;
};