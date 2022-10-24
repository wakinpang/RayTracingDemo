#include "Camera.h"

Camera::Camera(Point3 position, double width, double height, double focus) 
                : origin(position), width(width), height(height), focus(focus)
{
    horizontal = Vector3(width, 0, 0);
    vertical = Vector3(0, height, 0);
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focus);
}

Ray Camera::GetRay(double u, double v)
{
    return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}