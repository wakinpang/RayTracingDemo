#include "Lambertian.h"
#include "..\Shape\Shape.h"

Lambertian::Lambertian(const Color& att) : attenuation(att)
{
    
}

bool Lambertian::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
{
    Vector3 scatteredDirection = Normalize(result.Normal + Vector3::GetRandomPointInUnitSphere());
    scattered = Ray(result.Point, scatteredDirection);
    attenuation = this->attenuation;

    return true;
}