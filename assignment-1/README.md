# HPC-Embedde-Project 1
### Assignment 1

# Ubuntu 18.04
* Virtual Box

# Git

```bash
sudo apt-get install git # Instalar el git
git clone https://github.com/manchii/hpc-emb-prj1
```

Comandos

```bash
git status
git branch dj-b
git checkout dj-b
```


# Toolchain

```bash
sudo apt-get install gcc-arm-linux-gnueabihf
sudo apt-get install build-essentials
```



# Emulador: QEMU ARM

Instalar el QEMU en Ubuntu 18.04
```bash
sudo apt-get install qemu-system-arm
```

# Bootloader: U-boot 2019.04

Descargar el release desde el repo

```bash
wget ftp://ftp.denx.de/pub/u-boot/u-boot-2019.04.tar.bz2
```

Compilación
```bash
CROSS_COMPILE=arm-linux-gnueabihf-
ARCH=arm
make vexpress_ca9x4_defconfig CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
make all CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
qemu-system-arm -machine vexpress-a9 -nographic -no-reboot -kernel u-boot

```

# Kernel: Linux 5.1
```bash
wget https://github.com/torvalds/linux/archive/v5.1.zip
```

```bash
make vexpress_defconfig CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
make all CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
```

# File-System: BusyBox

```bash
sudo apt-get install libncurses5-dev
sudo apt-get install libncursesw5-dev
```

```bash
mkdir bb_build
make O=bb_build/ defconfig CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
make O=bb_build/ menuconfig CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
```
Marcar con 'y' en el menuconfig
* Seleccionar Settings -> (*) Build static binary (no shared libs)

```bash
make O=bb_build/ CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
cd bb_build/
make CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
make install CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
cd ../../ # salirse de BusyBox
# Hacer el ramdisk
mkdir initramfs
cd initramfs
mkdir etc && mkdir proc && mkdir sys
cp -av ../busybox-1.3.1/bb_build/_install/* ./
rm linuxrc
gedit init
```
Dentro del init se escribe el init script
```bash
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
echo -e "Hello World\n"
exec /bin/sh
```

```bash
chmod +x init
find ./ -print0 | cpio --null -ov --format=newc  > initramfs.cpio
```

Corriendo QEMU

```bash
cd Linux-5.1
cp ../initramfs/initramfs.cpio ./
qemu-system-arm -machine vexpress-a9 -cpu cortex-a9 -dtb ./arch/arm/boot/dts/vexpress-v2p-ca9.dtb -kernel ./arch/arm/boot/zImage -nographic -m 512M -append "earlyprintk=serial console=ttyAMA0" -initrd initramfs.cpio
```
