FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# provide full config for now (based on powernv_defconfig)
SRC_URI_append = " file://defconfig"
# SRC_URI_remove_qemuppc64 = "git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.8;destsuffix=${KMETA}"

COMPATIBLE_MACHINE_qemuppc64 = "${MACHINE}"
COMPATIBLE_MACHINE_qemuppc64le = "${MACHINE}"
