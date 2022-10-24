#pragma once

#include "Shape.h"

class Sphere : public Shape 
{
public:
    Sphere();
    Sphere(Vector3 pos, double radius);
    bool Hit(Ray ray, double tMin, double tMax, HitResult& result) override;
    void SetColor(Color color);

private:
    double radius;
    Color color;
};