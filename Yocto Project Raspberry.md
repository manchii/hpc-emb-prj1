
# Create your workspace
```bash
$ mkdir my_yocto && cd my_yocto
## Clone Git repos
# The build system
$ git clone -b thud git://git.yoctoproject.org/poky && cd poky
# Add specific meta for Raspberry Pi boards
$ git clone -b thud git://git.yoctoproject.org/meta-raspberrypi
```

#Dependencies
```bash
$ sudo apt install python-minimal

$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm
```

