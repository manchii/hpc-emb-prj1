# hpc-emb-prj1
Asignment 1 - Class of high performance computing embedded system

```bash
CROSS_COMPILE=arm-linux-gnueabihf-
ARCH=arm
make vexpress_ca9x4_defconfig CROSS_COMPILE=arm-linux-gnueabihf-
make all CROSS_COMPILE=arm-linux-gnueabihf-
qemu-system-arm -machine vexpress-a9 -nographic -no-reboot -kernel u-boot
```
