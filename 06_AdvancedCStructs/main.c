#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    CordinateDimension2D = 2,
    CordinateDimension3D = 3,
} CordinateDimension;

typedef struct
{
    CordinateDimension dimension;

    union
    {
        struct
        {
            int x;
            int y;
            int z;
        } d3;

        struct
        {
            int x;
            int y;
        } d2;
    };
} Cordinate;

Cordinate MakeCordinate2D(int x, int y)
{
    Cordinate c;
    c.dimension = CordinateDimension2D;
    c.d2.x = x;
    c.d2.y = y;
    return c;
}

Cordinate MakeCordinate3D(int x, int y, int z)
{
    Cordinate c;
    c.dimension = CordinateDimension3D;
    c.d3.x = x;
    c.d3.y = y;
    c.d3.z = z;
    return c;
}

void DoWork(Cordinate c)
{
    printf_s("Coridate with a order of %i\n", c.dimension);
    if (c.dimension == CordinateDimension2D)
    {
        printf_s("Coridate 2D: x: %i y: %i\n", c.d2.x, c.d2.y);
    }
    else if (c.dimension == CordinateDimension3D)
    {
        printf_s("Coridate 3D: x: %i y: %i z: %i\n", c.d3.x, c.d3.y, c.d3.z);
    }
}

int main()
{
    DoWork(MakeCordinate2D(5, 5));
    DoWork(MakeCordinate3D(5, 5, -5));
}
