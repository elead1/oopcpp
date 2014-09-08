#include "Triangle.h"

Triangle::Triangle(int s1, imt s2, int s3)
{
    side1 = s1;
    side2 = s2;
    side3 = s3;
}

char* Triangle::getType()
{
    if(side1 == side2 == side3)
    {
        return "equilateral";
    }
    else if((side1 == side2) || (side2 == side3) || (side1 == side3))
    {
        return "isoceles";
    }
    else
    {
        return "scalene";
    }
}
