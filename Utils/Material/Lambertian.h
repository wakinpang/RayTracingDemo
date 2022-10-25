#pragma once

#include "Material.h"
#include "..\Vector3.h"

class Lambertian : public Material
{
public:
    Lambertian(const Color& att);
    bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const override;

private:
    Color attenuation;
    Point3 randomPointInUnitSphere() const;
    double reflectRate;
};