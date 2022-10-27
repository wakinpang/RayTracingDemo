#include "Metal.h"
#include "..\Shape\Shape.h"

Metal::Metal(const Color& att, double f) : attenuation(att), fuzz(f > 1 ? 1 : f)
{

}

bool Metal::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
{
    auto normal = result.Normal;
    auto reflectedDir = reflect(rayIn.GetDirection(), normal);
    scattered = Ray(result.Point, reflectedDir + fuzz * Vector3::GetRandomPointInUnitSphere());
    attenuation = this->attenuation;
    return Dot(scattered.GetDirection(), normal) > 0;
}

Vector3 Metal::reflect(const Vector3& v, const Vector3& n) const
{
    return v - 2 * Dot(v, n) * n;
}