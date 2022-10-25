#pragma once

#include "Shape.h"

class Sphere : public Shape 
{
public:
    Sphere();
    Sphere(Vector3 pos, double radius, std::shared_ptr<Material> material);
    bool Hit(Ray ray, double tMin, double tMax, HitResult& result) override;

private:
    double radius;
    std::shared_ptr<Material> mat;
};