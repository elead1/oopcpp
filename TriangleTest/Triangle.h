#include <iostream>

class Triangle
{
    private:
        int side1, side2, side3;
    
    public: 
        Triangle();
        Triangle(int s1, int s2, int s3);
        char* getType(); 
};

