#@TYPE: Machine
#@NAME: QEMU PPC 64 machine
#@DESCRIPTION: Machine configuration for running a PPC 64 system on QEMU

require conf/machine/include/qemu.inc
require conf/machine/include/tune-power9.inc

KERNEL_IMAGETYPE = "vmlinux"

SERIAL_CONSOLES ?= "115200;ttyS0 115200;ttyS1"

################################################################################
# some old  stuff from qemuppc64 from https://github.com/akuster/meta-qemu-bsps/blob/master/conf/machine/qemuppc64.conf
# are thoose still necessary?
# prelink broken on ppc64
# USER_CLASSES_remove = "image-prelink"
# IMAGE_PREPROCESS_COMMAND_remove = "prelink_image;"
# TARGET_CC_KERNEL_ARCH = "-mno-spe"
# KERNEL_IMAGETYPE = "vmlinux"
################################################################################

# For runqemu
QB_SYSTEM_NAME = "qemu-system-ppc64"
QB_MACHINE = "-machine powernv"
QB_CPU = "-cpu power9"
QB_KERNEL_CMDLINE_APPEND = "console=tty console=ttyS0"
QB_OPT_APPEND = "-device qemu-xhci -device usb-tablet -device usb-kbd"
# Virtio Networking support
QB_TAP_OPT = "-netdev tap,id=net0,ifname=@TAP@,script=no,downscript=no"
# Virtio serial console
QB_SERIAL_OPT = "-device virtio-serial-device -chardev null,id=virtcon -device virtconsole,chardev=virtcon"
QB_TCPSERIAL_OPT = "-device virtio-serial-device -chardev socket,id=virtcon,port=@PORT@,host=127.0.0.1 -device virtconsole,chardev=virtcon"
# QEMU complains with following warning if there is not enough memory:
# warning: skiboot may not work with < 1GB of RAM
QB_MEM = "-m 1024"
