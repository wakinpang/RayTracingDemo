#include "World.h"
#include "Material/Material.h"
#include "Constants.h"

World::World(Camera cam) : cam(cam)
{
    shapes = std::vector<std::shared_ptr<Shape>>();
}

void World::AddShape(std::shared_ptr<Shape> obj)
{
    shapes.push_back(obj);
}

void World::Render(int width, int height)
{
    // ppm header
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for (int i = height - 1; i >= 0; i--)
    {
        std::cerr << "\rRemaining lines: " << i << std::flush;
        for (int j = 0; j < width; j++)
        {
            Color pixelColor(0, 0, 0);

            for (int c = 0; c < sampleCount; c++) 
            {
                double u = (j + GetRandomDouble()) / (width - 1);
                double v = (i + GetRandomDouble()) / (height - 1);

                Ray r = cam.GetRay(u, v);
                //std::cerr << "Origin:" << r.GetOrigin() << "Direction:" << r.GetDirection() << std::endl; 

                pixelColor += rayColor(r, Constants::maxDepth);
            }

            pixelColor /= sampleCount;
            writeColor(pixelColor);
        }
    }
}

Color World::rayColor(Ray ray, int depth)
{
    // if this ray has scattered for enough times, treat it as did not hit anything
    if (depth == 0)
    {
        return Color(0, 0, 0);
    } 

    auto count = shapes.size();
    bool hit = false;
    double farthest = Constants::infinity;
    HitResult finalRes;

    for (int i = 0; i < count; i++)
    {
        HitResult result;
        if (shapes[i]->Hit(ray, 0.001, farthest, result)) // tMin 0.001, to ignore the ray that is really short
        {
            hit = true;
            farthest = result.Value;
            finalRes = result;
        }
    }

    if (hit)
    {
        Color attenuation;
        Ray scatteredRay;
        bool scattered = finalRes.Material->Scatter(ray, finalRes, attenuation, scatteredRay);
        if (scattered)
        {
            return attenuation * rayColor(scatteredRay, depth - 1);
        }
        else
        {
            // if not scattered, absorb all rays
            return Color(0, 0, 0);
        }
    }

    // no hit, return background color
    Vector3 normalizedDir = Normalize(ray.GetDirection());
    double t = 0.5 * (normalizedDir.GetY() + 1.0);

    return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1);
}

void World::writeColor(Color& color)
{
    // gamma-correct, which gamma = 2
    double r = std::sqrt(color.GetX());
    double g = std::sqrt(color.GetY());
    double b = std::sqrt(color.GetZ());

    std::cout << (int)(256 * Clamp(r, 0, 0.999)) << ' '
              << (int)(256 * Clamp(g, 0, 0.999)) << ' '
              << (int)(256 * Clamp(b, 0, 0.999)) << '\n';
}