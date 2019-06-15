//Version 0.1

# Code snippet

> Implementación del algoritmo RGB --> YUV

```c++
#include <iostream>

using vect3 = double*;
void RGB2YUV(vect3 RGB, vect3 YUV){
//  0.299   R  0.587   G  0.114   B
// -0.14713 R -0.28886 G  0.436   B
//  0.615   R -0.51499 G -0.10001 B
  YUV[0] = 0.299*RGB[0]   +0.587*RGB[1]   +0.114*RGB[2];
  YUV[1] = -0.14713*RGB[0]-0.28886*RGB[1] +0.436*RGB[2];
  YUV[2] = 0.615*RGB[0]   -0.51499*RGB[1] -0.10001*RGB[2];
};
int main() {
  double YUV[] = {0.0,0.0,0.0};
  double RGB[3] = {1.0,0.0,0.0};
  RGB2YUV(RGB, YUV);
}
```
