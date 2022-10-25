#pragma once

#include "Shape/Shape.h"
#include "Camera.h"
#include <vector>
#include <memory>

class World
{
public:
    World(Camera cam);

    void AddShape(std::shared_ptr<Shape> obj);
    void Render(int width, int height);

private:
    std::vector<std::shared_ptr<Shape>> shapes;
    int sampleCount = 128;
    Camera cam;

    Color rayColor(Ray ray, int depth);
    void writeColor(Color& color);
};