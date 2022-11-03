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
    Camera cam;

    Color rayColor(Ray ray, int depth);
    void writeColor(Color& color);

    Color randomSample(int width, int height, int i, int j);
    Color stratifiedSample(int width, int height, int i, int j);
    Color stratifiedSampleWithJittering(int width, int height, int i, int j);
    Color nRooksSample(int width, int height, int i, int j);
};