#include "Panel.h"

Panel::Panel(Point3 pos, const Vector3& h, const Vector3& v, std::shared_ptr<Material> mat) : 
    Shape(pos), horizontal(h), vertical(v), material(mat)
{

}

bool Panel::Hit(Ray ray, double tMin, double tMax, HitResult& result)
{
    auto normal = Normalize(Cross(horizontal, vertical));
    if (Dot(normal, ray.GetDirection()) == 0) // if this ray is parallel with panel, return false
    {
        return false;
    }

    auto t = Dot(normal, (ray.GetOrigin() - position)) / Dot(normal, -ray.GetDirection());

    if (t < tMin || t > tMax) 
    {
        return false;
    }

    auto p = ray.At(t);
    auto panelVector = p - position;

    auto horizonLengthSquare = horizontal.LengthSquare();
    auto verticalLengthSquare = vertical.LengthSquare();

    auto m = Dot(panelVector, horizontal) / horizonLengthSquare;
    auto n = Dot(panelVector, vertical) / verticalLengthSquare;
    if (m < 0 || m > 1 || n < 0 || n > 1) // although intersecting with this panel, but not in the range
    {
        return false;
    }

    result.SetSideNormal(ray.GetDirection(), normal);
    result.Material = material;
    result.Point = p;
    result.Value = t;

    return true;
} 