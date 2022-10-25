#pragma once

#include "..\Ray.h"

struct HitResult;

class Material
{
public:
    virtual bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const = 0;
};