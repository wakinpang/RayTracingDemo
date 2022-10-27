#pragma once

#include "Material.h"

class DiffuseLight : public Material
{
public:
    DiffuseLight(const Color& att, double d);
    bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const override;

private:
    Color attenuation;
    double diffuse;
};