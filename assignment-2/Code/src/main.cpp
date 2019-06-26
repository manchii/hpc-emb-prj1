/*---------------------------rgb2yuv main----------------------------------/
This code targets c++17 standard
/----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <chrono>
#include "parseArgs.hpp"
#include "rgb2yuv.hpp"

template<typename Container>
void loadImage(const Config &config, Container &rgbBuffer){
  auto inputFile = std::ifstream{config._rgbFile,std::ios::binary|std::ios::ate};
  if(!inputFile.good()){
    std::cout<<"File "<<config._rgbFile<<" not found!\n";
    std::exit(EXIT_FAILURE);
  }
  const auto height = config._height;
  const auto width = config._width;
  const auto sizeFile = inputFile.tellg();
  const auto pixelBytes = 24/8; //8 bits per color channel
  if(sizeFile!=(height*width*pixelBytes)){
    std::cout<<"File "<<config._rgbFile<<" does not fit with the dimensiones given.\n";
    std::exit(EXIT_FAILURE);
  }
  rgbBuffer.resize(sizeFile);
  const auto refToVec = reinterpret_cast<char*>(rgbBuffer.data());
  inputFile.seekg(0, std::ios::beg);
  inputFile.read(refToVec,sizeFile);
  inputFile.close();
}
void saveImage(const Config &config, std::vector<uint8_t> &buffer){
  auto outFile = std::ofstream(config._yuvFile, std::ios::binary);
  outFile.write(reinterpret_cast<char *>(buffer.data()),buffer.size());
  outFile.close();
}

struct YUVPlanes{
  std::vector<uint8_t> buffer;
  uint8_t* y;
  uint8_t* u;
  uint8_t* v;
  // Each channel is allocated in one buffer
  // references y,u,v hold the base pointer to
  // each pixel plane
  YUVPlanes(const uint size):buffer(size){
    y=&buffer[0];u=&buffer[size/3];v=&buffer[size*2/3];
  }
};

int main(int argc, char** argv){
  const auto config=makeConfig(argc,argv);
  auto rgb_ch = std::vector<uint8_t>{};
  loadImage(config,rgb_ch);
  const auto planesSize=rgb_ch.size();
  auto yuv_ch = YUVPlanes(planesSize);
  auto start = std::chrono::system_clock::now();
  RGB2YUV(rgb_ch,yuv_ch);
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout<<"Duration of convertion: "<<elapsed.count()<<"us\n";
  saveImage(config,yuv_ch.buffer);
}
