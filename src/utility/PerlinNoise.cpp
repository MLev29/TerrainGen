#include "PerlinNoise.h"

float PerlinNoise(float x, float y)
{
    // Determine grid cell corner coords
    int x0 = (int) x;
    int y0 = (int) y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Calculate interpolation weights
    float sx = x - (float) x0;
    float sy = y - (float) y0;

    // Compute and interpolate top corners
    float n0 = DotGridGradient(x0, y0, x, y);
    float n1 = DotGridGradient(x1, y0, x, y);
    
    float interpolatedX0 = Interpolate(n0, n1, sx);

    // Compute and interpolate bottom corners
    n0 = DotGridGradient(x0, y1, x, y);
    n1 = DotGridGradient(x1, y1, x, y);

    float interpolatedX1 = Interpolate(n0, n1, sx);

    // Interpolate via vertical weight
    return Interpolate(interpolatedX0, interpolatedX1, sy);
}

math::Vector2<float> Hash(int x, int y)
{
    constexpr unsigned w = 8 * sizeof(unsigned);
    constexpr unsigned s = w / 2;
    unsigned a = x;
    unsigned b = y;
    a *= 3284157443;

    b ^= a << s | a >> (w - s);
    b *= 1911520717;

    a ^= b << s | b >> (w - s);
    a *= 2048419325;

    float random = a * (PI / ~(~0u >> 1));

    return math::Vector2<float>(
        sin(random),
        cos(random)
    );
}

float DotGridGradient(int x1, int y1, float x2, float y2)
{
    math::Vector2<float> gradient = Hash(x1, y1);

    float dx = x2 - (float) x1;
    float dy = y2 - (float) y1;

    return dx * gradient[0] + dy * gradient[1];
}

float Interpolate(float a, float b, float weight)
{
    // Cubic interpolation
    return (b - a) * (3.0f - weight * 2.0f) * weight * weight + a;
}