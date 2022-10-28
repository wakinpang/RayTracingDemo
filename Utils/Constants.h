#pragma once

#include <limits>
#include <cmath>
#include <random>

class Constants
{
public:
    static constexpr double pi = 3.1415926535897932385;
    static constexpr double infinity = std::numeric_limits<double>::infinity();
    static constexpr int maxDepth = 50;
    static constexpr int sampleCount = 256;
};

inline double GetRandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 gen;
    return distribution(gen);
}

inline double GetRandomDouble(double min, double max)
{
    return min + (max - min) * GetRandomDouble();
}

inline double Clamp(double v, double min, double max)
{
    if (v < min) 
    {
        return min;
    }

    if (v > max)
    {
        return max;
    }

    return v;
}