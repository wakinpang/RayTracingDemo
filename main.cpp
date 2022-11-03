#include "Utils/Vector3.h"
#include "Utils/Camera.h"
#include "Utils/Shape/Sphere.h"
#include "Utils/World.h"
#include "Utils/Material/Lambertian.h"
#include "Utils/Material/Metal.h"
#include "Utils/Material/DiffuseLight.h"
#include "Utils/Shape/Panel.h"

int main()
{
    auto camera = Camera(Point3(0, 0, 0), 2 * 16 / 9.0, 2, 1);
    auto world = World(camera);

    auto lambertianBlue = std::make_shared<Lambertian>(Color(0.4, 0.4, 0.8));
    auto lambertianGreen = std::make_shared<Lambertian>(Color(0.4, 0.8, 0.4));
    auto lambertianGray = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    auto MetalGreen = std::make_shared<Metal>(Color(0.9, 0.9, 0.9), 0.01);
    auto lightWhite = std::make_shared<DiffuseLight>(Color(2, 2, 2), 0);

    auto blueSphere = std::make_shared<Sphere>(Point3(0, 0, -1.5), 0.5, lambertianBlue);
    //auto greenSphere = std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, MetalGreen);
    auto lightSphere = std::make_shared<Sphere>(Point3(-1, 1.5, -2), 1, lightWhite);

    auto backPanel = std::make_shared<Panel>(Point3(-3, -3, -2), Vector3(6, 0, 0), Vector3(0, 6, 0), lambertianGray);
    auto leftPanel = std::make_shared<Panel>(Point3(-3, -3, -2), Vector3(0, 0, 2), Vector3(0, 6, 0), lambertianBlue);
    auto rightPanel = std::make_shared<Panel>(Point3(1.5, -3, -2), Vector3(0, 0, 2), Vector3(0, 6, 0), MetalGreen);
    auto groundPanel = std::make_shared<Panel>(Point3(-5, -0.5, 5), Vector3(10, 0, 0), Vector3(0, 0, -10), lambertianGray);

    world.AddShape(blueSphere);
    world.AddShape(lightSphere);
    //world.AddShape(backPanel);
    //world.AddShape(leftPanel);
    world.AddShape(rightPanel);
    world.AddShape(groundPanel);

    world.Render(800, 450);

    return 0;
}