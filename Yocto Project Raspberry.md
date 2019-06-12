
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

# Setup the yocto environnement by sourcing the oe init script

```bash
$ . oe-init-build-env ../build
```

#Result
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
$ vim build/conf/bblayers.conf
```


