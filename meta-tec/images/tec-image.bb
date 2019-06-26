SUMMARY = "A console development image with some C/C++ dev tools"

require ../../meta-rpi/images/console-image.bb

#IMAGE_INSTALL += " \
#    rgb2yuv \
#    rgb2yuv_intrinsics \
#"
IMAGE_INSTALL += "rgb2yuv-c"
IMAGE_INSTALL += "rgb2yuv-intrinsics"

export IMAGE_BASENAME = "tec-image"
