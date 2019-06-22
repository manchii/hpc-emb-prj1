SUMMARY = "A console development image with some C/C++ dev tools"



DESCRIPTION = "Simple helloworld application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"


SRC_URI = "file://main.cpp \
	   file://parseArgs.hpp \
	   file://rgb2yuv.hpp \
"
do_compile(){
	${CXX} main.cpp -o rgb2yuv_c -std=c++17 -lm -O3
}

do_install() {
	install -d ${D}${bindir}
	install -m 0777 rgb2yuv_c ${D}${bindir} 
}

require ../../../../poky/meta/recipes-core/images/core-image-base.bb
export IMAGE_BASENAME = "tec-image"

#inherit core-image-base
