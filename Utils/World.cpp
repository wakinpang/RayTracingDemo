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
            Color pixelColor = randomSample(width, height, i, j);
            
            writeColor(pixelColor);
        }
    }
}

Color World::randomSample(int width, int height, int i, int j)
{
    Color pixelColor(0, 0, 0);
    for (int c = 0; c < Constants::sampleCount; c++) 
    {
        double u = (j + GetRandomDouble()) / (width - 1);
        double v = (i + GetRandomDouble()) / (height - 1);

        Ray r = cam.GetRay(u, v);
        //std::cerr << "Origin:" << r.GetOrigin() << "Direction:" << r.GetDirection() << std::endl; 

        pixelColor += rayColor(r, Constants::maxDepth);
    }

    pixelColor /= Constants::sampleCount;

    return pixelColor;
}

Color World::stratifiedSample(int width, int height, int i, int j)
{
    Color pixelColor(0, 0, 0);
    auto sqrtC = std::floor(std::sqrt(Constants::sampleCount));
    auto unitSquareLength = cam.GetHeight() / (width * sqrtC);
    auto halfUnitSquareLength = unitSquareLength / 2;

    double u = j / (width - 1.0);
    double v = i / (height - 1.0);

    for (int m = 0; m < sqrtC; m++)
    {
        for (int n = 0; n < sqrtC; n++)
        {
            Ray r = cam.GetRay(u + m * unitSquareLength + halfUnitSquareLength, v + n * unitSquareLength + halfUnitSquareLength); // no jittering
            pixelColor += rayColor(r, Constants::maxDepth);
        }
    }

    pixelColor /= (sqrtC * sqrtC);

    return pixelColor;
}

Color World::stratifiedSampleWithJittering(int width, int height, int i, int j)
{
    Color pixelColor(0, 0, 0);
    auto sqrtC = std::floor(std::sqrt(Constants::sampleCount));
    auto unitSquareLength = cam.GetHeight() / (width * sqrtC);

    double u = j / (width - 1.0);
    double v = i / (height - 1.0);

    for (int m = 0; m < sqrtC; m++)
    {
        for (int n = 0; n < sqrtC; n++)
        {
            Ray r = cam.GetRay(u + m * unitSquareLength + GetRandomDouble() * unitSquareLength, v + n * unitSquareLength + GetRandomDouble() * unitSquareLength); // no jittering
            pixelColor += rayColor(r, Constants::maxDepth);
        }
    }

    pixelColor /= (sqrtC * sqrtC);

    return pixelColor;
}

Color World::nRooksSample(int width, int height, int i, int j)
{
    struct rookCol
    {
        int line;
        double u;
        double v;
    };

    Color pixelColor(0, 0, 0);
    auto unitSquareLength = cam.GetHeight() / (width * Constants::sampleCount);
    std::vector<rookCol> cols;

    double u = j / (width - 1.0);
    double v = i / (height - 1.0);

    for (int m = 0; m < Constants::sampleCount; m++)
    {
        auto col = rookCol();

        double t = m * unitSquareLength;
        double u = t + GetRandomDouble() * unitSquareLength;
        double v = t + GetRandomDouble() * unitSquareLength;

        col.line = m;
        col.u = u;
        col.v = v;

        cols.push_back(col);
    }

    // shuffle
    auto len = cols.size();
    for (int m = 0; m < len; m++)
    {
        auto randomTarget = std::floor(GetRandomDouble(0, len));
        auto tempCol = cols[randomTarget];
        cols[randomTarget] = cols[m];
        cols[m] = tempCol;
    }

    // sampling
    for (int m = 0; m < len; m++)
    {
        Ray r = cam.GetRay(u + m * unitSquareLength + cols[m].u, v + cols[m].line * unitSquareLength + cols[m].v);
        pixelColor += rayColor(r, Constants::maxDepth);
    }

    pixelColor /= Constants::sampleCount;
    
    return pixelColor;
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
            return attenuation;
        }
    }

    // no hit, ambient light
    return Color(0.2, 0.2, 0.2);
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