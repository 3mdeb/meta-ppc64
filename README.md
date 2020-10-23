# meta-ppc64

The goal is to provide `ppc64` QEMU targets for modern `ppc64` systems.

Currently available targets:
- `qemuppc64` - targets
  [IBM POWER9 architecture](https://en.wikipedia.org/wiki/POWER9) (Big Endian)

  ```
  SHELL=/bin/bash kas-docker -shell meta-ppc64/kas-be.yml
  ```

- `qemuppc64le` - targets
  [IBM POWER9 architecture](https://en.wikipedia.org/wiki/POWER9) (Little Endian)

  ```
  SHELL=/bin/bash kas-docker -shell meta-ppc64/kas-be.yml
  ```

## Notes

* Big endian `zImage.epapr` build fails at:

```
WARNING: linux-yocto-5.8.13+gitAUTOINC+34775c20bc_5981001bf0-r0 do_package_qa: QA Issue: kernel-image-zimage.epapr: ELF binary /boot/zImage.epapr-5.8.13-yocto-standard has relocations in .text [textrel]
ERROR: linux-yocto-5.8.13+gitAUTOINC+34775c20bc_5981001bf0-r0 do_package_qa: QA Issue: Architecture did not match (PowerPC, expected Unknown (21)) in /boot/zImage.epapr-5.8.13-yocto-standard [arch]
WARNING: linux-yocto-5.8.13+gitAUTOINC+34775c20bc_5981001bf0-r0 do_package_qa: QA Issue: kernel-vmlinux: ELF binary /boot/vmlinux-5.8.13-yocto-standard has relocations in .text [textrel]
ERROR: linux-yocto-5.8.13+gitAUTOINC+34775c20bc_5981001bf0-r0 do_package_qa: QA run found fatal errors. Please consider fixing them.
ERROR: Logfile of failure stored in: /work/build/tmp/work/qemuppc64-poky-linux/linux-yocto/5.8.13+gitAUTOINC+34775c20bc_5981001bf0-r0/temp/log.do_package_qa.13057
ERROR: Task (/work/poky/meta/recipes-kernel/linux/linux-yocto_5.8.bb:do_package_qa) failed with exit code '1'
NOTE: Tasks Summary: Attempted 4072 tasks of which 3977 didn't need to be rerun and 1 failed.
```
  - skipped for now


* Why readelf reports the Big Endian image to be 32bit? It is likely the reason
  of Yocto QA check trigger?

```
readelf -h zImage.epapr_be

ELF Header:
  Magic:   7f 45 4c 46 01 02 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, big endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           PowerPC
  Version:                           0x1
  Entry point address:               0x20000000
  Start of program headers:          52 (bytes into file)
  Start of section headers:          7237480 (bytes into file)
  Flags:                             0x8000, relocatable-lib
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         3
  Size of section headers:           40 (bytes)
  Number of section headers:         19
  Section header string table index: 18

readelf -h zImage.epapr_le

ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           PowerPC64
  Version:                           0x1
  Entry point address:               0x20000000
  Start of program headers:          64 (bytes into file)
  Start of section headers:          7309688 (bytes into file)
  Flags:                             0x2, abiv2
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         3
  Size of section headers:           64 (bytes)
  Number of section headers:         18
  Section header string table index: 17
```
