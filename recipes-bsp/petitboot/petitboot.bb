SRC_URI = "file://petitboot.conf"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

S = "${WORKDIR}"

do_install() {
    install -d -m 0644 ${D}/boot/petitboot.conf
    install -m 0644 ${S}/petitboot.conf ${D}/boot/petitboot.conf
}

FILES_${PN} += "/boot"
