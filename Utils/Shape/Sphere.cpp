#include "Sphere.h"

Sphere::Sphere(Vector3 pos, double radius) : Shape(pos)
{
    this->radius = radius;
}

bool Sphere::Hit(Ray ray, double tMin, double tMax, HitResult& result)
{
    auto op = ray.GetOrigin() - position;
    auto dir = ray.GetDirection();

    auto a = dir.LengthSquare();
    auto b = 2.0 * Dot(op, dir);
    auto c = op.LengthSquare() - radius * radius;

    auto delta = b * b - 4 * a * c;

    // if (dir.GetY() < 0.3 && dir.GetX() > -0.3 && dir.GetX() < 0.3 && dir.GetY() > -0.3) {
    //     std::cerr << "Origin: " << ray.GetOrigin() << " Direction: " << dir << " Delta: " << delta << std::endl;
    //     std::cerr << a << " " << b << " " << c << std::endl;
    // }

    if (delta < 0)
    {
        return false;
    }

    auto sqrtDelta = std::sqrt(delta);
    auto root = (-b - sqrtDelta) / 2 * a;
    if (root < tMin || root > tMax)
    {
        root = (-b + sqrtDelta) / 2 * a;
        if (root < tMin || root > tMax)
        {
            return false;
        }
    }

    result.Value = root;
    result.Point = ray.At(root);

    // set hit color
    result.Color = color;

    auto outNormal = Normalize(result.Point - position);
    result.SetSideNormal(ray.GetDirection(), outNormal);

    return true;
}

void Sphere::SetColor(Color color)
{
    this->color = color;
}