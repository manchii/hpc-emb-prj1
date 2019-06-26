# Part 1: Create your workspace

# Require packages
```bash
$ sudo apt install python-minimal

$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm
```

Locate your workspace folder then

```bash
$ mkdir my_yocto && cd my_yocto
## Clone Git repos
# First the main Yocto project poky layer
~# git clone -b warrior git://git.yoctoproject.org/poky.git poky-warrior
```

# Clone the dependency repositories
```bash
~$ cd poky-warrior
~/poky-warrior$ git clone -b warrior git://git.openembedded.org/meta-openembedded
~/poky-warrior$ git clone -b warrior https://github.com/meta-qt5/meta-qt5
~/poky-warrior$ git clone -b warrior git://git.yoctoproject.org/meta-raspberrypi
```

# Clone the meta-rpi repository
```bash
~$ mkdir ~/rpi
~$ cd ~/rpi
~/rpi$ git clone -b warrior git://github.com/jumpnow/meta-rpi
```

# Initialize the build directory
```bash
##You could manually create the directory structure like this
$ mkdir -p ~/rpi/build/conf

```
# Customize the configuration files
```bash
# Copy them to the build/conf directory (removing the ‘-sample’)
~/rpi$ cp meta-rpi/conf/local.conf.sample build/conf/local.conf
~/rpi$ cp meta-rpi/conf/bblayers.conf.sample build/conf/bblayers.conf
```

# Edit bblayers.conf

## Important: In bblayers.conf file replace ${HOME} with the appropriate path to the meta-layer repositories on your system if you modified any of the paths in the previous instructions.

```bash
#The machine in this case is raspberrypi2, make sure only one is uncommented
MACHINE = "raspberrypi2"

#Modified the bblayers.conf as following:
DL_DIR = "${HOME}/rpi/build/sources"
SSTATE_DIR = "${HOME}/rpi/build/sstate-cache"
TMPDIR = "${HOME}/rpi/build/tmp"
```

# # Setup the yocto environnement by sourcing the oe init script

```bash
~/Documents/SEAD/my_yocto/poky-warrior$ source oe-init-build-env ../rpi/build/

## This is the output

### Shell environment set up for builds. ###

You can now run 'bitbake '

Common targets are:
    core-image-minimal
    core-image-sato
    meta-toolchain
    meta-toolchain-sdk
    adt-installer
    meta-ide-support

You can also run generated qemu images with a command like 'runqemu qemux86'
~/rpi/build$
```

# Build a very first Image
```bash
~/rpi/build$ bitbake console-image
```
# Part#2: Format the MicroSD

 1. Plug in your removable flash drive and run the ‘lsblk’ command to identify the device.

Here is the output of the 'lsblk' command on my system where ‘sdb’ is the removable flash storage:
```bash
NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
sdb    8:16   1  3.8G  0 disk
├─sdb2   8:18   1  2.4M  0 part
└─sdb1   8:17   1  1.5G  0 part /media/sandisk 
```

 2.  Exchange ‘sdb’ with the name of your block device in the following command: 
```bash
sudo parted /dev/sdb
```
 3. 
```bash
(parted) mklabel msdos
```
 4.  Once the partition table is created, you can create partitions on the drive. We will be creating just one partition: 
```bash
(parted) mkpart primary fat32 1MiB 100%
```
 5. Then set the boot flag on it: 
```bash
(parted) set 1 boot on
```
 6. Exit the parted tool:
```bash 
(parted) quit 
```
# Part#3: Copying the image to the SD card
Please find the correct microSDcard, there are 2 ways, in this case "lsblk"
```bash
~/rpi/meta-rpi$ fdisk -l

# or

~/rpi/meta-rpi$ lsblk

# Output
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
loop0    7:0    0  14,8M  1 loop /snap/gnome-characters/284
loop1    7:1    0   2,3M  1 loop /snap/gnome-calculator/260
loop2    7:2    0 140,7M  1 loop /snap/gnome-3-26-1604/86
loop3    7:3    0  34,6M  1 loop /snap/gtk-common-themes/818
loop4    7:4    0   205M  1 loop /snap/atom/232
loop5    7:5    0 151,2M  1 loop /snap/gnome-3-28-1804/55
loop6    7:6    0  14,5M  1 loop /snap/gnome-logs/45
loop7    7:7    0   3,7M  1 loop /snap/gnome-system-monitor/87
loop8    7:8    0     4M  1 loop /snap/gnome-calculator/406
loop9    7:9    0  88,4M  1 loop /snap/core/6964
loop10   7:10   0   205M  1 loop /snap/atom/231
loop11   7:11   0  14,8M  1 loop /snap/gnome-characters/288
loop12   7:12   0   3,7M  1 loop /snap/gnome-system-monitor/91
loop13   7:13   0    91M  1 loop /snap/core/6350
loop14   7:14   0   8,4M  1 loop /snap/nmap/249
loop15   7:15   0  35,3M  1 loop /snap/gtk-common-themes/1198
loop16   7:16   0 140,7M  1 loop /snap/gnome-3-26-1604/88
loop17   7:17   0  1008K  1 loop /snap/gnome-logs/61
loop18   7:18   0 151,2M  1 loop /snap/gnome-3-28-1804/59
loop19   7:19   0  53,7M  1 loop /snap/core18/970
sda      8:0    0   100G  0 disk 
└─sda1   8:1    0   100G  0 part /
sdc       8:16   1   7.4G  0 disk
|-sdb1    8:17   1    64M  0 part
`-sdb2    8:18   1   7.3G  0 part
sr0     11:0    1  1024M  0 rom
```
In order to excecute the below command, open the terminal where the .rpi-sdimg is located or write the correct path. The "console-image-raspberrypi2.rpi-sdimg" is the image file and the /dev/sdc is the SD card.

WARNING: Make sure to change /dev/sdc according to your microSD,  I will use sdc for the card on this machine.

```bash
sudo dd bs=4M if=console-image-raspberrypi2.rpi-sdimg of=/dev/sdc status=progress conv=fsync
# Output

566231040 bytes (566 MB, 540 MiB) copied, 3 s, 188 MB/s
136+0 records in
136+0 records out
570425344 bytes (570 MB, 544 MiB) copied, 119,689 s, 4,8 MB/s

# If there is an error with fsync, please reboot the machine.
```

# Part#4: Install your MicroSD in the raspberrypi2
Only the first time it will required to change the password.

The login user is root with password jumpnowtek.


# Using the Raspberry Pi Camera
To get access to config.txt, mount the boot partition first
```bash
root@rpi# mkdir /mnt/fat
root@rpi# mount /dev/mmcblk0p1 /mnt/fat
root@rpi# nano /mnt/fat/config.txt
```
Then edit
```bash
start_x=1
gpu_mem=128
disable_camera_led=1   # optional for disabling the red LED on the camera
```

Save and reboot.

#Take first photo
```bash
root@rpi2# raspiyuv -w 640 -h 480 -bgr -o image.brg
```

# Part 5: Create the new recipe 

# Setup the yocto environnement by sourcing the oe init script

```bash
~/Documents/SEAD/my_yocto/poky-warrior$ source oe-init-build-env ../rpi/build/
# Output
### Shell environment set up for builds. ###

You can now run 'bitbake <target>'

Common targets are:
    core-image-minimal
    core-image-sato
    meta-toolchain
    meta-ide-support

You can also run generated qemu images with a command like 'runqemu qemux86'
```
Once your environment is setup you can see the layers that compose the BSP using the command:

```bash
~/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers show-layers

# Output

NOTE: Starting bitbake server...
layer                 path                                      priority
==========================================================================
meta                  /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta  5
meta-poky             /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-poky  5
meta-oe               /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-oe  6
meta-multimedia       /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-multimedia  6
meta-networking       /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-networking  5
meta-perl             /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-perl  6
meta-python           /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-python  7
meta-qt5              /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-qt5  7
meta-raspberrypi      /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-raspberrypi  9
meta-rpi              /home/alebermudez94/Documents/SEAD/my_yocto/rpi/meta-rpi  16
```

# Create a layer name: "meta-tec"
```bash
~/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers add-layer ../meta-tec 
```

# Add new layer to bblayers.conf
```bash
/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers add-layer ../meta-tec
```

# Check the new layer is added
```bash
~/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers show-layers

# Output

NOTE: Starting bitbake server...
layer                 path                                      priority
==========================================================================
meta                  /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta  5
meta-poky             /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-poky  5
meta-oe               /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-oe  6
meta-multimedia       /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-multimedia  6
meta-networking       /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-networking  5
meta-perl             /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-perl  6
meta-python           /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-openembedded/meta-python  7
meta-qt5              /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-qt5  7
meta-raspberrypi      /home/alebermudez94/Documents/SEAD/my_yocto/poky-warrior/meta-raspberrypi  9
meta-rpi              /home/alebermudez94/Documents/SEAD/my_yocto/rpi/meta-rpi  16
meta-tec              /home/alebermudez94/Documents/SEAD/my_yocto/rpi/meta-tec  6

```

# Create the location for the new recipes,  name: “recipes-tec”
```bash
~/Documents/SEAD/my_yocto/rpi/build$ mkdir ../meta-tec/recipes-tec
```
# Create directory for Recipe#1,  name: “rgb2yuv”
```bash
~/Documents/SEAD/my_yocto/rpi/build$ mkdir ../meta-tec/recipes-tec/rgb2yuv

```
# Copy example of iqaudio-mute_1.0 to the recipe,  name: “rgb2yuv.bb”
```bash
/Documents/SEAD/my_yocto/rpi/build$ cp ../meta-rpi/recipes-misc/iqaudio-mute/iqaudio-mute_1.0.bb ../meta-tec/recipes-tec/rgb2yuv/rgb2yuv.bb
```

# Change the name,  name: “rgb2yuv.bb”
```bash
/Documents/SEAD/my_yocto/rpi/build$ cp ../meta-rpi/recipes-misc/iqaudio-mute/iqaudio-mute_1.0.bb ../meta-tec/recipes-tec/rgb2yuv/rgb2yuv.bb
```

# copy file example,  name: “rgb2yuv.bb”
```bash
/Documents/SEAD/my_yocto/rpi/build$ cp ../meta-rpi/recipes-misc/iqaudio-mute/iqaudio-mute_1.0.bb ../meta-tec/recipes-tec/rgb2yuv/rgb2yuv.bb
```

# copy file folder example,  name: “files”
```bash
~/Documents/SEAD/my_yocto/rpi/build$ cp -r ../meta-rpi/recipes-misc/iqaudio-mute/files/ ../meta-tec/recipes-tec/rgb2yuv/
```
# Open manually "rgb2yuv.bb", change all the text:
```bash
SUMMARY = "A console development image with some C/C++ dev tools"
HOMEPAGE = "NO information"
SECTION = "meta-tec"

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

require ../../../meta-rpi/images/console-image.bb
export IMAGE_BASENAME = "tec-image"

#inherit core-image-base
```

# Delete the "init" document in the example
```bash
~/Documents/SEAD/my_yocto/rpi/build$ rm ../meta-tec/recipes-tec/rgb2yuv/files/init
```
 
# Download the .cpp documents manually

#Show the recipes image
```bash
~/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers show-recipes "*image*"

# Output

NOTE: Starting bitbake server...
Loading cache: 100% |########################################################| Time: 0:00:00
Loaded 3541 entries from dependency cache.
=== Matching recipes: ===
ap-image:
  meta-rpi             1.0
audio-image:
  meta-rpi             1.0
build-appliance-image:
  meta                 15.0.0
console-basic-image:
  meta-rpi             1.0
console-image:
  meta-rpi             1.0
core-image-base:
  meta                 1.0
core-image-clutter:
  meta                 1.0
core-image-full-cmdline:
  meta                 1.0
core-image-kernel-dev:
  meta                 1.0
core-image-lsb:
  meta                 unknown (skipped)
core-image-lsb-dev:
  meta                 unknown (skipped)
core-image-lsb-sdk:
  meta                 unknown (skipped)
core-image-minimal:
  meta                 1.0
core-image-minimal-dev:
  meta                 1.0
core-image-minimal-initramfs:
  meta                 unknown (skipped)
core-image-minimal-mtdutils:
  meta                 1.0
core-image-rt:
  meta                 unknown (skipped)
core-image-rt-sdk:
  meta                 unknown (skipped)
core-image-sato:
  meta                 1.0
core-image-sato-dev:
  meta                 1.0
core-image-sato-sdk:
  meta                 1.0
core-image-sato-sdk-ptest:
  meta                 1.0
core-image-testmaster:
  meta                 1.0
core-image-testmaster-initramfs:
  meta                 unknown (skipped)
core-image-tiny-initramfs:
  meta                 unknown (skipped)
core-image-weston:
  meta                 unknown (skipped)
core-image-x11:
  meta                 unknown (skipped)
flask-image:
  meta-rpi             1.0
gumsense-image:
  meta-rpi             1.0
imagemagick:
  meta-oe              7.0.8_35
iot-image:
  meta-rpi             1.0
libsdl-image:
  meta-oe              1.2.12
libsdl2-image:
  meta-oe              2.0.3
meta-multimedia-image:
  meta-multimedia      1.0
meta-multimedia-image-base:
  meta-multimedia      1.0
meta-networking-image:
  meta-networking      1.0
meta-networking-image-base:
  meta-networking      1.0
meta-oe-image:
  meta-oe              1.0
meta-oe-image-base:
  meta-oe              1.0
meta-oe-ptest-image:
  meta-oe              1.0
meta-perl-image:
  meta-perl            1.0
meta-perl-ptest-image:
  meta-perl            1.0
meta-python-image:
  meta-python          1.0
meta-python-image-base:
  meta-python          1.0
meta-python-ptest-image:
  meta-python          1.0
ovmf-shell-image:
  meta                 1.0
py3qt-image:
  meta-rpi             1.0
qt5-basic-image:
  meta-rpi             1.0
qt5-image:
  meta-rpi             1.0
qtimageformats:
  meta-qt5             5.12.3+gitAUTOINC+5e433bcefa
rpi-basic-image:
  meta-raspberrypi     1.0
rpi-hwup-image:
  meta-raspberrypi     1.0
rpi-test-image:
  meta-raspberrypi     1.0
xcb-util-image:
  meta                 0.4.0 (skipped)

```
#Add extra path for the layer.conf in the meta-tec, copy and replace the following text in /Documents/SEAD/my_yocto/build/meta-tec/conf
```bash
# We have a conf and classes directory, add to BBPATH
BBPATH .= ":${LAYERDIR}"

# We have recipes-* directories, add to BBFILES
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
	    ${LAYERDIR}/recipes-*/*.bb \	
            ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "meta-tec"
BBFILE_PATTERN_meta-tec = "^${LAYERDIR}/"
BBFILE_PRIORITY_meta-tec = "6"

LAYERDEPENDS_meta-tec = "core"
LAYERSERIES_COMPAT_meta-tec = "warrior"


# Find in all recipes the file named: rgb2yuv
```bash
~/Documents/SEAD/my_yocto/rpi/build$ bitbake-layers show-recipes "*rgb2yuv*"
# Output 
how-recipes "*rgb2yuv*"
NOTE: Starting bitbake server...
Loading cache: 100% |########################################################| Time: 0:00:00
Loaded 3541 entries from dependency cache.
=== Matching recipes: ===
rgb2yuv:
  meta-tec             1.0

```
# Generate the image
```bash
bitbake rgb2yuv
```

# Copying the image to the SD card
```bash
sudo dd bs=4M if=tec-image-raspberrypi2.rpi-sdimg of=/dev/sdc status=progress conv=fsync

# Output

566231040 bytes (566 MB, 540 MiB) copied, 3 s, 188 MB/s
136+0 records in
136+0 records out
570425344 bytes (570 MB, 544 MiB) copied, 119,689 s, 4,8 MB/s

# If there is an error with fsync, please reboot the machine.
```




```bash

```










