#pragma once

#include "LibMath/vector/Vector2.h"

float PerlinNoise(float x, float y);

math::Vector2<float> Hash(int x, int y);
float DotGridGradient(int x1, int y1, float x2, float y2);
float Interpolate(float a, float b, float weight);

//float PerlinNoiseV2(float x, float y);
//math::Vector2<float> Grad(math::Vector2<float> point);
//float Fade(float t);
