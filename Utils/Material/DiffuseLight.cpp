#include "DiffuseLight.h"
#include "..\Shape\Shape.h"

DiffuseLight::DiffuseLight(const Color& att, double d) : attenuation(att), diffuse(d)
{

}

bool DiffuseLight::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
{
    auto inverseDir = -rayIn.GetDirection();
    attenuation = Dot(inverseDir, result.Normal) > diffuse ? this->attenuation : Color(0, 0, 0);

    return false;
}