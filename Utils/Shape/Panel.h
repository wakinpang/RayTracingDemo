#pragma once

#include "Shape.h"

class Panel : public Shape
{
public:
    Panel(Point3 pos, const Vector3& horizontal, const Vector3& vertical, std::shared_ptr<Material> mat);
    bool Hit(Ray ray, double tMin, double tMax, HitResult& result) override;

private:
    Vector3 horizontal;
    Vector3 vertical;
    std::shared_ptr<Material> material;
};