#ifndef __ARM_NEON__
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

#else

#include <arm_neon.h>
template<typename ContRGB,typename ContYUV>
void RGB2YUV(const ContRGB RGB, ContYUV YUV) noexcept {
  uint indexRGB; uint indexYUV;
  for(indexRGB=0,indexYUV=0; indexRGB<RGB.size(); indexRGB+=24,indexYUV+=8){
    const uint8x8x3_t rgb = vld3_u8(&RGB[indexRGB]);
    const uint8x8_t &r8 = rgb.val[0];
    const uint8x8_t &g8 = rgb.val[1];
    const uint8x8_t &b8 = rgb.val[2];
    const auto R16 = vreinterpretq_s16_u16(vmovl_u8(r8));
    const auto G16 = vreinterpretq_s16_u16(vmovl_u8(g8));
    const auto B16 = vreinterpretq_s16_u16(vmovl_u8(b8));
    auto Y16 = int16x8_t{128,128,128,128,128,128,128,128};
    auto U16 = int16x8_t{128,128,128,128,128,128,128,128};
    auto V16 = int16x8_t{128,128,128,128,128,128,128,128};
    auto c1  = int16x8_t{66 ,66 ,66 ,66 ,66 ,66 ,66 ,66 };
    auto c2  = int16x8_t{129,129,129,129,129,129,129,129};
    auto c3  = int16x8_t{25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 };
    vmlaq_s16(R16, c1, Y16);
    vmlaq_s16(G16, c2, Y16);
    vmlaq_s16(B16, c3, Y16);
    c1 = int16x8_t{38,38,38,38,38,38,38,38};
    c2 = int16x8_t{74,74,74,74,74,74,74,74};
    c3 = int16x8_t{112,112,112,112,112,112,112,112};
    vmlsq_s16(R16, c1, U16);
    vmlsq_s16(G16, c2, U16);
    vmlaq_s16(B16, c3, U16);
    c1 = int16x8_t{112,112,112,112,112,112,112,112};
    c2 = int16x8_t{94,94,94,94,94,94,94,94};
    c3 = int16x8_t{18,18,18,18,18,18,18,18};
    vmlaq_s16(R16, c1, V16);
    vmlsq_s16(G16, c2, V16);
    vmlsq_s16(B16, c3, V16);
    Y16 = vshrq_n_s16 (Y16, 8);
    U16 = vshrq_n_s16 (U16, 8);
    V16 = vshrq_n_s16 (V16, 8);
    c1 = int16x8_t{16 ,16 ,16 ,16 ,16 ,16 ,16 ,16 };
    c2 = int16x8_t{128,128,128,128,128,128,128,128};
    Y16 = vaddq_s16(Y16, c1);
    U16 = vaddq_s16(U16, c2);
    V16 = vaddq_s16(V16, c2);
    auto y8 = vreinterpret_s8_u8(vmovn_s16(Y16));
    auto u8 = vreinterpret_s8_u8(vmovn_s16(U16));
    auto v8 = vreinterpret_s8_u8(vmovn_s16(V16));
    vst1_u8(&YUV.y[indexYUV],y8);
    vst1_u8(&YUV.u[indexYUV],u8);
    vst1_u8(&YUV.v[indexYUV],v8);
  }
}
#endif
