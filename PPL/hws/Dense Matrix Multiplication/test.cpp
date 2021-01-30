#include <iostream>
#include <omp.h>

int main()
{
#pragma omp parallel for
    for (char i = 'a'; i <= 'z'; i++)
        std::cout << i << std::endl;
    return 0;
}