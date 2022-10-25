#include "Lambertian.h"
#include "..\Shape\Shape.h"

Lambertian::Lambertian(const Color& att) : attenuation(att)
{
    
}

bool Lambertian::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
{
    Vector3 scatteredDirection = Normalize(result.Normal + randomPointInUnitSphere());
    scattered = Ray(result.Point, scatteredDirection);
    attenuation = this->attenuation;

    return true;
}

Point3 Lambertian::randomPointInUnitSphere() const
{
    while (true)
    {
        Point3 p = Vector3::Random(-1, 1);
        if (p.LengthSquare() >= 1)
        {
            continue;
        }

        return p;
    }
}