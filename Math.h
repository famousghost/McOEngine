#pragma once
namespace McOEngine
{
namespace Math
{
    struct float3
    {
        float3(float x, float y, float z)
            :x(x), y(y), z(z)
        {}

        float x;
        float y;
        float z;

        float operator[](int i)
        {
            if (i == 0)
            {
                return x;
            }
            if (i == 1)
            {
                return y;
            }
            return z;
        }
    };

    struct float2
    {
        float2(float x, float y)
            :x(x), y(y)
        {}

        float x;
        float y;

        float operator[](int i)
        {
            if (i == 0)
            {
                return x;
            }
            return y;
        }
    };
}
}