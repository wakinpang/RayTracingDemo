#include "World.h"
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

                pixelColor += rayColor(r);
            }

            pixelColor /= sampleCount;
            writeColor(pixelColor);
        }
    }
}

Color World::rayColor(Ray ray)
{
    auto count = shapes.size();
    for (int i = 0; i < count; i++)
    {
        HitResult result;
        if (shapes[i]->Hit(ray, 0, Constants::infinity, result))
        {
            return result.Color;
        }
    }

    // no hit, return background color
    Vector3 normalizedDir = Normalize(ray.GetDirection());
    double t = 0.5 * (normalizedDir.GetY() + 1.0);

    return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1);
}

void World::writeColor(Color& color)
{
    double r = color.GetX();
    double g = color.GetY();
    double b = color.GetZ();

    std::cout << (int)(256 * Clamp(r, 0, 0.999)) << ' '
              << (int)(256 * Clamp(g, 0, 0.999)) << ' '
              << (int)(256 * Clamp(b, 0, 0.999)) << '\n';
}