#include "Utils/Vector3.h"
#include "Utils/Camera.h"
#include "Utils/Shape/Sphere.h"
#include "Utils/World.h"

int main()
{
    auto camera = Camera(Point3(0, 0, 0), 1.6, 0.9, 1);
    auto world = World(camera);

    auto blueSphere = std::make_shared<Sphere>(Point3(0, 0, -1), 0.5);
    blueSphere->SetColor(Color(0, 0, 128));
    auto greenSphere = std::make_shared<Sphere>(Point3(0, -100.5, -1), 100);
    greenSphere->SetColor(Color(0, 128, 0));

    world.AddShape(blueSphere);
    world.AddShape(greenSphere);

    world.Render(800, 450);

    return 0;
}