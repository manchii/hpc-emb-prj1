#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unistd.h>
#include <getopt.h>

struct Config{
  uint height=0;
  uint width=0;
  std::string rgb_file;
  std::string yuv_file;
  bool exec=false;
};

void printUsage(){
  std::cout<<
  "./rgb2yuv [-i RGBfile][-o YUVfile][-h][-a]\n\n"<<
  "-i RGBfile specifies the RGB file to be converted.\n\n"<<
  "-o YUVfile specifies the output file name.\n\n"<<
  "-a displays the information of the author of the program.\n\n"<<
  "-h displays the usage message to let the user know how to execute the application.\n\n"
}

// Config makeConfig(int argc, char** argv){
//   int opt;
//   Config config;
//   while((opt = getopt(argc, argv, "ah")) != -1){
//     switch(opt){
//       case 'a':
//       case 'h':
//       case 'r':
//         std::cout<<"option:"<< opt <<"\n"
//         break;
//       case '?':
//         printf("unknown option: %c\n", optopt);
//         break;
//       default:
//         printUsage();
//         break;
//     }
//   }
//   return config;
// }

template<typename Pointer>
void RGB2YUV(const Pointer RGB, Pointer YUV) noexcept {
//  0.299   R  0.587   G  0.114   B
// -0.14713 R -0.28886 G  0.436   B
//  0.615   R -0.51499 G -0.10001 B
  YUV[0] = 0.299*RGB[0]   +0.587*RGB[1]   +0.114*RGB[2];
  YUV[1] = -0.14713*RGB[0]-0.28886*RGB[1] +0.436*RGB[2];
  YUV[2] = 0.615*RGB[0]   -0.51499*RGB[1] -0.10001*RGB[2];
}

template<typename Container>
void printCode(const Container Pix) noexcept {
  for(auto &color : Pix){
    std::cout << "\t" << color;
  } std::cout << "\n";
}

int main(int argc, char** argv){
  using pixel = std::array<double,3>;
//  auto config=makeConfig(argc,argv);

  auto YUV = pixel{0.0,0.0,0.0};
  auto RGB = pixel{1.0,0.0,0.0};
  RGB2YUV(RGB.data(), YUV.data());
  std::cout<<"YUV:";
  printCode(YUV);
  std::cout<<"RGB:";
  printCode(RGB);
}
