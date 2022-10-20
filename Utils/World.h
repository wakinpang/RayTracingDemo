#pragma once

#include "Shape/Shape.h"
#include <vector>

class World
{
public:
    World();

    void AddShap(Shape& obj);
    void Render();

private:
    std::vector<Shape> shapes;
};