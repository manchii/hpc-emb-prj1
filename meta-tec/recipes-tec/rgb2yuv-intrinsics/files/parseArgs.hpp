#include <unistd.h>
#include <getopt.h>

struct Config{
  uint _height=0;
  uint _width=0;
  std::string _rgbFile="";
  std::string _yuvFile="out.yuv";
  void printInfo()const noexcept{
    std::cout<<
    "Input image file: "<<_rgbFile<<'\n'<<
    "\tdimensions: "<<_width<<"x"<<_height<<'\n'<<
    "Output image file: "<<_yuvFile<<"\n\n";
  }
  bool notValid()const{
    bool valid = (_rgbFile!="")&&(_height>0)&&(_width>0);
    return !valid;
 }
};

void printUsage(){
  std::cout<<
  "./rgb2yuv_c [-i RGBfile][-H height][-W width][-o YUVfile][-h][-a]\n\n"<<
  "-H RGB image height. REQUIRED\n"<<
  "-W RGB image width. REQUIRED\n"<<
  "-i RGBfile specifies the RGB file to be converted. REQUIRED\n"<<
  "-o YUVfile specifies the output file name.\n"<<
  "-a displays the information of the author of the program.\n"<<
  "-h displays the usage message to let the user know how to execute the application.\n";
}
void printAbout(){
  std::cout<<
  "Developed by:\n"<<
  "Alejandro Bermudez\tEmail: alebermudez94@gmail.com\n"<<
  "Douglas Mora Ceciliano\tEmail: dmc220190@gmail.com\n"<<
  "David Ramirez Arroyo\tEmail: djosera22@gmail.com\n"<<
  "Kaleb Alfaro Badilla\tEmail: kaleb.23415@gmail.com\n";
}

Config makeConfig(int argc, char** argv){
  int opt;
  Config config;
  while((opt = getopt(argc, argv, "H:W:i:oah")) != -1){
    switch(opt){
      case 'H':
        config._height=std::atoi(optarg);
        break;
      case 'W':
        config._width=std::atoi(optarg);
      break;
      case 'i':
        config._rgbFile=optarg;
        break;
      case 'o':
        config._yuvFile=optarg;
        break;
      case 'a':
        printAbout();
        exit(EXIT_SUCCESS);
        break;
      case 'h':
        printUsage();
        exit(EXIT_SUCCESS);
        break;
      case '?':
        printUsage();
        exit(EXIT_FAILURE);
        break;
    }
  }
  config.printInfo();
  if(config.notValid()){
    std::cout<<"Not valid configuration!\n ";
    exit(EXIT_FAILURE);
  }
  return config;
}
