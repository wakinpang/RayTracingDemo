#include "Utils/Vector3.h"
#include "Utils/Camera.h"
#include "Utils/Shape/Sphere.h"
#include "Utils/World.h"
#include "Utils/Material/Lambertian.h"

int main()
{
    auto camera = Camera(Point3(0, 0, 0), 2 * 16 / 9.0, 2, 1);
    auto world = World(camera);

    auto lambertianBlue = std::make_shared<Lambertian>(Color(0.4, 0.4, 1));
    auto lambertianGreen = std::make_shared<Lambertian>(Color(0.4, 1, 0.4));

    auto blueSphere = std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, lambertianBlue);
    auto greenSphere = std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, lambertianGreen);

    world.AddShape(blueSphere);
    world.AddShape(greenSphere);

    world.Render(800, 450);

    return 0;
}