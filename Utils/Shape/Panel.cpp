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

    auto t = Dot(normal, (ray.GetOrigin() - position)) / Dot(normal, ray.GetDirection());
} 