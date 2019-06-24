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
template <typename T>
void printVec(T vect,int size=8){
  std::cout << "Vec: ";
  for(int i=0; i<size; i++){
    std::cout << +vect[i] <<"__";
  }
  std::cout << "\n";
}

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
    auto Y16 = int16x8_t{64,64,64,64,64,64,64,64};
    auto U16 = int16x8_t{64,64,64,64,64,64,64,64};
    auto V16 = int16x8_t{64,64,64,64,64,64,64,64};

    auto c1  = int16x8_t{33 ,33 ,33 ,33 ,33 ,33 ,33 ,33 };
    auto c2  = int16x8_t{65,65,65,65,65,65,65,65};
    auto c3  = int16x8_t{13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 };
    Y16=vmlaq_s16(Y16, c1, R16);
    Y16=vmlaq_s16(Y16, c2, G16);
    Y16=vmlaq_s16(Y16, c3, B16);
    c1 = int16x8_t{19,19,19,19,19,19,19,19};
    c2 = int16x8_t{37,37,37,37,37,37,37,37};
    c3 = int16x8_t{56,56,56,56,56,56,56,56};
    U16=vmlsq_s16(U16, c1, R16);
    U16=vmlsq_s16(U16, c2, G16);
    U16=vmlaq_s16(U16, c3, B16);
    c1 = int16x8_t{56,56,56,56,56,56,56,56};
    c2 = int16x8_t{47,47,47,47,47,47,47,47};
    c3 = int16x8_t{9,9,9,9,9,9,9,9};
    V16=vmlaq_s16(V16, c1, R16);
    V16=vmlsq_s16(V16, c2, G16);
    V16=vmlsq_s16(V16, c3, B16 );
    Y16 = vshrq_n_s16 (Y16, 7);
    U16 = vshrq_n_s16 (U16, 7);
    V16 = vshrq_n_s16 (V16, 7);
    c1 = int16x8_t{16 ,16 ,16 ,16 ,16 ,16 ,16 ,16 };
    c2 = int16x8_t{128,128,128,128,128,128,128,128};
    Y16 = vaddq_s16(Y16, c1);
    U16 = vaddq_s16(U16, c2);
    V16 = vaddq_s16(V16, c2);
    auto y8 = vreinterpret_u8_s8(vmovn_s16(Y16));
    auto u8 = vreinterpret_u8_s8(vmovn_s16(U16));
    auto v8 = vreinterpret_u8_s8(vmovn_s16(V16));
    vst1_u8(&YUV.y[indexYUV],y8);
    vst1_u8(&YUV.u[indexYUV],u8);
    vst1_u8(&YUV.v[indexYUV],v8);
  }
}
#endif
