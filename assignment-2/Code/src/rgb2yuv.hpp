template<typename ContRGB,typename ContYUV>
void RGB2YUV(const ContRGB RGB, ContYUV YUV) noexcept {
  uint indexRGB;
  uint indexYUV;
  for(indexRGB=0,indexYUV=0; indexRGB<RGB.size(); indexRGB+=3,indexYUV++){
    int y;int u;int v;
    const int r=RGB[indexRGB];
    const int g=RGB[indexRGB+1];
    const int b=RGB[indexRGB+2];
    #define SATURATE(X) (X<0)?0 : (X<255?X:255);
    y = SATURATE(((66*r+129*g+25*b+128)>>8)+16);
    u = SATURATE(((-38*r-74*g+112*b+128)>>8)+128);
    v = SATURATE(((112*r-94*g-18*b+128)>>8)+128);
    YUV.y[indexYUV]=static_cast<uint8_t>(y);
    YUV.u[indexYUV]=static_cast<uint8_t>(u);
    YUV.v[indexYUV]=static_cast<uint8_t>(v);
  }
}
#include "src/dsp/neon.h"
void RGB2YUVNeon(int8_t const *RGB, int8_t *YUV) noexcept {
  for(indexRGB=0,indexYUV=0; indexRGB<RGB.size(); indexRGB+=24,indexYUV+=8){
    int8x8x3_t rgb=vld3_u8(&RGB[indexRGB]);
    uint8x8_t y8;uint8x8_t u8;uint8x8_t v8;
    uint16x8_t Y16;uint16x8_t U16;uint16x8_t V16;
    uint16x8_t c1;uint16x8_t c2;uint16x8_t c3;
    const uint8x8_t &r8=rgb.val[0];
    const uint8x8_t &g8=rgb.val[1];
    const uint8x8_t &b8=rgb.val[2];
    const uint16x8_t R16 = vmovl_u8(r8);
    const uint16x8_t G16 = vmovl_u8(g8);
    const uint16x8_t B16 = vmovl_u8(b8);
    vduph_laneq_s16 (Y16, 128);
    vduph_laneq_s16 (U16, 128);
    vduph_laneq_s16 (V16, 128);
    vduph_laneq_s16 (c1, 66);
    vduph_laneq_s16 (c2, 129);
    vduph_laneq_s16 (c3, 25);
    vmlaq_s16 (R16, c1, Y16);
    vmlaq_s16 (G16, c2, Y16);
    vmlaq_s16 (B16, c3, Y16);
    vduph_laneq_s16 (c1, 38);
    vduph_laneq_s16 (c2, 74);
    vduph_laneq_s16 (c3, 112);
    vmlsq_s16 (R16, c1, U16);
    vmlsq_s16 (G16, c2, U16);
    vmlaq_s16 (B16, c3, U16);
    vduph_laneq_s16 (c1, 112);
    vduph_laneq_s16 (c2, 94);
    vduph_laneq_s16 (c3, 18);
    vmlaq_s16 (R16, c1, V16);
    vmlsq_s16 (G16, c2, V16);
    vmlsq_s16 (B16, c3, V16);
    Y16=vshrq_n_s16 (Y16, 8);
    U16=vshrq_n_s16 (U16, 8);
    V16=vshrq_n_s16 (V16, 8);
    vduph_laneq_s16 (c1, 16);
    vduph_laneq_s16 (c2, 128);
    Y16=vadd_s16 (Y16, C1);
    U16=vadd_s16 (U16, C2);
    V16=vadd_s16 (V16, C2);
    y8=vmovn_s16(Y16);
    u8=vmovn_s16(Y16);
    v8=vmovn_s16(Y16);
    YUV.y[indexYUV]=vstl_s8(&YUV.y[indexYUV],y8);
    YUV.u[indexYUV]=vstl_s8(&YUV.y[indexYUV],u8);
    YUV.v[indexYUV]=vstl_s8(&YUV.y[indexYUV],v8);
    
  }
}


