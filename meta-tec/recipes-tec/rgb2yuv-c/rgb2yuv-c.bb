#
# This file was derived from the 'rgb2yuv' example recipe in the
# 
#

DESCRIPTION = "rgb2yuv_c"
SECTION = "recipes-tec"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=0ec5801450d6b777d973eb956c021332"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRCREV = "c96b1fdd0767a9a13b9fca9d91fd3975c44c9de4"
# SRC_URI = "git://github.com/gbmhunter/YoctoHelloWorldApp.git"
SRC_URI = "file://main.cpp \
	   file://parseArgs.hpp \
	   file://rgb2yuv.hpp \
	   file://LICENSE \
	   file://Makefile.am \
	   file://configure.ac \
	   file://800x608c.brg \	
	   file://outc.yuv \
           file://c_results.pdf \

"
S = "${WORKDIR}"

do_install_append() {
      install -d ${D}/rgb2yuv-docs
      cp ${WORKDIR}/outc.yuv /${D}/rgb2yuv-docs
      cp ${WORKDIR}/800x608c.brg /${D}/rgb2yuv-docs
      cp ${WORKDIR}/c_results.pdf /${D}/rgb2yuv-docs	  	
}
FILES_${PN} += "/rgb2yuv-docs"

inherit autotools

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""

