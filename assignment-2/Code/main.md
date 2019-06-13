//Version 0.1

#include <iostream>

#define vect3 double*


vect3 RGB2YUV(double RGB[3], double YUV[3]){
  
//   0.299   0.587   0.114
//  -0.14713  -0.28886   0.436
//   0.615  -0.51499  -0.10001
  YUV[0]=0.299*RGB[0]+0.587*RGB[1]+0.114*RGB[2];
  std::cout << YUV[0] << "\n";
  YUV[1]=-0.14713*RGB[0]-0.28886*RGB[1]+0.436*RGB[2];
  std::cout << YUV[1] << "\n";
  YUV[2]=0.615*RGB[0]+-0.51499*RGB[1]+-0.10001*RGB[2];
  std::cout << YUV[2] << "\n";
  return YUV;
};

int main() {
  std::cout << "Hello World!\n";
  double YUV[3];
  double RGB[3];
  RGB[0]=1;
  RGB[1]=0.0;
  RGB[2]=0.0;
  RGB2YUV(RGB, YUV);
}
