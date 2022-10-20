#include "World.h"

World::World()
{
    shapes = std::vector<Shape>();
}

void World::AddShap(Shape& obj)
{
    shapes.push_back(obj);
}


void World::Render()
{
    
}