#pragma once

#include "Material.h"

class Metal : public Material
{
public:
    Metal(const Color& att, double f);
    bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const override;
private:
    double fuzz;
    Color attenuation;

    Vector3 reflect(const Vector3& v, const Vector3& n) const;
};