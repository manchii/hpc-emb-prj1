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
make vexpress_defconfig CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
make all CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm
```
