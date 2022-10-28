#include "DiffuseLight.h"
#include "..\Shape\Shape.h"

DiffuseLight::DiffuseLight(const Color& att, double d) : attenuation(att), diffuse(d)
{

}

bool DiffuseLight::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
{
    attenuation = this->attenuation;

    return false;
}