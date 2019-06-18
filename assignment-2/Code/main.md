//Version 0.1

# Code snippet

> Implementación del algoritmo RGB --> YUV

```c++

#include <iostream>

//using vect3 = double*;
using vect3 = unsigned char[3];

void RGB2YUV (vect3 RGB, vect3 YUV)
{
//  Con punto fijo
//  66  R+129 G+ 25 B
// -38  R+-74 G+112 B
//  112 R+-94 G+-18 B

  YUV[0] = ((66 * RGB[0] + 129 * RGB[1] + 25 * RGB[2] + 128) >> 8) + 16;
  YUV[1] = ((-38 * RGB[0] - 74 * RGB[1] + 112 * RGB[2] + 128) >> 8) + 128;
  YUV[2] = ((112 * RGB[0] - 94 * RGB[1] - 18 * RGB[2] + 128) >> 8) + 128;

};

int main ()
{
  int R=0;
  int G=255;
  int B=255;
  vect3 YUV = {0,0,0};
  vect3 RGB = {R,G,B};
  RGB2YUV(RGB, YUV);
  std::cout<<+YUV[0]<<"\n";
  std::cout<<+YUV[1]<<"\n";
  std::cout<<+YUV[2]<<"\n";
}

```
