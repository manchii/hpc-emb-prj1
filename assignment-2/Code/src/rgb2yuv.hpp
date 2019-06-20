template<typename ContRGB,typename ContYUV>
void RGB2YUV(const ContRGB RGB, ContYUV YUV) noexcept {
  uint indexRGB;
  uint indexYUV;
  for(indexRGB=0,indexYUV=0; indexRGB<RGB.size(); indexRGB+=3,indexYUV++){
    int y;int u;int v;
    const int r=RGB[indexRGB];
    const int g=RGB[indexRGB+1];
    const int b=RGB[indexRGB+2];
    y = ((66*r+129*g+25*b+128)>>8)+16;
    u = ((-38*r-74*g+112*b+128)>>8)+128;
    v = ((112*r-94*g-18*b+128)>>8)+128;
    y = y<255?y:255; y = y<0?0:y;
    u = u<255?u:255; u = u<0?0:u;
    v = v<255?v:255; v = v<0?0:v;
    YUV.y[indexYUV]=static_cast<uint8_t>(y);
    YUV.u[indexYUV]=static_cast<uint8_t>(u);
    YUV.v[indexYUV]=static_cast<uint8_t>(v);
  }
}
