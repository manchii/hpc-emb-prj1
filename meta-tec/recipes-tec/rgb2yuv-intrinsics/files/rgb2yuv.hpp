
#ifndef NEON

/*---------------------------Generic_Version----------------------------------/
This code serves as a placeholder for non-NEON compatible processor (ARMCPU)
The precision used is 8-bits signed fixed-point.
This implementation assumes RGB888 packed format and converts it to YUV(4:4:4)p
/----------------------------------------------------------------------------*/
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

/*-----------------------------NEON_Intrinsics_Version-------------------------/
In this section the code is being represented with intrisics for NEON
This helps to perform 8 opertions per instruction which helps to improve
the performance of the program.
Note that in this case the 7-bits signed fixed-point of pecision is being
used instead of the 8-bits that are being used in the previous version (Generic Version).
Thus, the following coefficients are divided by two from the previous
implementation.
XXX For more information check the attached spreadsheet in the
    repository (Description_RGB2YUVNEON) XXX
/-----------------------------------------------------------------------------*/
//tested with cflags -march=armv7 -mfpu=neon -mfloat-abi=hard
#include <arm_neon.h>
template<typename ContRGB,typename ContYUV>
void RGB2YUV(const ContRGB RGB, ContYUV YUV) noexcept {
  uint indexRGB; uint indexYUV;
  for(indexRGB=0,indexYUV=0; indexRGB<RGB.size(); indexRGB+=24,indexYUV+=8){
    //vld3_u8
    //RGBRGBRGBRGBRGBRGBRGBRGB
    //to
    //RRRRRRRR
    //GGGGGGGG
    //BBBBBBBB
    const uint8x8x3_t rgb = vld3_u8(&RGB[indexRGB]);

    //Assign Var
    const uint8x8_t &r8 = rgb.val[0];
    const uint8x8_t &g8 = rgb.val[1];
    const uint8x8_t &b8 = rgb.val[2];

    //Change from 8x8 to 16x8
    const auto R16 = vreinterpretq_s16_u16(vmovl_u8(r8));
    const auto G16 = vreinterpretq_s16_u16(vmovl_u8(g8));
    const auto B16 = vreinterpretq_s16_u16(vmovl_u8(b8));

    //This macro calculate the equation Y=((c1*R+c2*G+c3*B)>>7)+c4
    #define EQUATION(R,G,B,c1,c2,c3,c4,S){\
    	auto Y16 = int16x8_t{64,64,64,64,64,64,64,64};\
	auto c  = int16x8_t{c1 ,c1 ,c1 ,c1 ,c1 ,c1 ,c1 ,c1 };\
	Y16=vmlaq_s16(Y16, c, R);\
	c  = int16x8_t{c2 ,c2 ,c2 ,c2 ,c2 ,c2 ,c2 ,c2 };\
	Y16=vmlaq_s16(Y16, c, G);\
	c  = int16x8_t{c3 ,c3 ,c3 ,c3 ,c3 ,c3 ,c3 ,c3 };\
	Y16=vmlaq_s16(Y16, c, B);\
	Y16 = vshrq_n_s16 (Y16, 7);\
	c = int16x8_t{c4 ,c4 ,c4 ,c4 ,c4 ,c4 ,c4 ,c4 };\
	Y16 = vaddq_s16(Y16, c);\
	auto y8 = vreinterpret_u8_s8(vmovn_s16(Y16));\
	vst1_u8(&S,y8);}

    //Evaluate macro with:
    //Y=((33*R+65*G+13*B)>>7)+16
    //U=((-19*R+-37*G+56*B)>>7)+128
    //V=((56*R+-47*G+-9*B)>>7)+128
    EQUATION(R16,G16,B16,33,65,13,16,YUV.y[indexYUV]);
    EQUATION(R16,G16,B16,-19,-37,56,128,YUV.u[indexYUV]);
    EQUATION(R16,G16,B16,56,-47,-9,128,YUV.v[indexYUV]);
  }
}
#endif
