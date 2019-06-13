
# Create your workspace

Locate your workspace folder then

```bash
$ mkdir my_yocto && cd my_yocto
## Clone Git repos
# The build system
$ git clone -b thud git://git.yoctoproject.org/poky && cd poky
# Add specific meta for Raspberry Pi boards
$ git clone -b thud git://git.yoctoproject.org/meta-raspberrypi
```

# Dependencies
```bash
$ sudo apt install python-minimal

$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm
```

# Setup the yocto environnement by sourcing the oe init script

```bash
$ . oe-init-build-env ../build
```

# Result
```bash
You had no conf/local.conf file. This configuration file has therefore been
created for you with some default values. You may wish to edit it to, for
example, select a different MACHINE (target hardware). See conf/local.conf
for more information as common configuration options are commented.
You had no conf/bblayers.conf file. This configuration file has therefore been
created for you with some default values. To add additional metadata layers
into your configuration please add entries to conf/bblayers.conf.
The Yocto Project has extensive documentation about OE including a reference
manual which can be found at:
    http://yoctoproject.org/documentation
For more information about OpenEmbedded see their website:
    http://www.openembedded.org/
### Shell environment set up for builds. ###
You can now run 'bitbake <target>'
Common targets are:
    core-image-minimal
    core-image-sato
    meta-toolchain
    meta-ide-support

```

#“Raspberry Pi” has to be declared into the build system of Yocto
```bash
$ cd ..
```

```bash
$ vim build/conf/bblayers.conf
```

#the bblayer should has something like this:

```bash
# POKY_BBLAYERS_CONF_VERSION is increased each time build/conf/bblayers.conf
# changes incompatibly
POKY_BBLAYERS_CONF_VERSION = "2"
BBPATH = "${TOPDIR}"
BBFILES ?= ""
BBLAYERS ?= " \
  /home/wp_user/workspace/my_yocto/poky/meta \
  /home/wp_user/workspace/my_yocto/poky/meta-poky \
  /home/wp_user/workspace/my_yocto/poky/meta-yocto-bsp \
  /home/wp_user/workspace/my_yocto/poky/meta-raspberrypi \
  "
```
****** Be carefully with the path in my case I used:*****

```bash
/home/david/Desktop/high-embedded/my_yocto/poky/....
```


Yocto step is to choose the target machine. Raspberry Pi are ashamedly not mentioned among default machine choices because it comes from the meta-raspberrypi, so it must be added manually as showed below. All possible machines are available into “my_yocto/poky/meta-raspberrypi/conf/machine/”

In our case is: raspberrypi2

```bash
$ vim build/conf/local.conf
```

The Modification should be like this:

```bash
[...]
# This sets the default machine to be qemux86 if no other machine is selected:
#MACHINE ??= "qemux86"
MACHINE ??= "raspberrypi3"
[...]
```

# Build a very first Image

```bash
$ bitbake core-image-base
```


