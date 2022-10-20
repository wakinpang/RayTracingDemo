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

    if (delta < 0)
    {
        return false;
    }

    auto root = (-b - std::sqrt(delta)) / 2 * a;
}