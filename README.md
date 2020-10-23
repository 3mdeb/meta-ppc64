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

* Cannot get the login prompt (both on LE or BE builds):

- can just stuck:

```
[    3.076659] udevd (79) used greatest stack depth: 10024 bytes left
[    3.092691] udevd[80]: starting eudev-3.2.9
[    5.186145] EXT4-fs (vda): re-mounted. Opts: (null)
[    5.186906] ext4 filesystem being remounted at / supports timestamps until 2038 (0x7fffffff)
[    7.370678] urandom_read: 4 callbacks suppressed
[    7.370816] random: dd: uninitialized urandom read (512 bytes read)
```

- or could even crash (depending on the serial QEMU params):

```
[    1.374644] Driver 'hvc_console' was unable to register with bus_type 'vio' because the bus was not initialized.
[    1.376651] hvc0: raw protocol on /ibm,opal/consoles/serial@0 (boot console)
[    1.377099] hvc0: No interrupts property, using OPAL event
[    1.380151] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    1.387642] printk: console [ttyS0] disabled
[    1.389410] BUG: Unable to handle kernel data access on read at 0xc00a0000000003e9
[    1.389927] Faulting instruction address: 0xc0000000008d79f4
[    1.390532] Oops: Kernel access of bad area, sig: 11 [#1]
[    1.390812] LE PAGE_SIZE=64K MMU=Radix SMP NR_CPUS=2048 NUMA PowerNV
[    1.391331] Modules linked in:
[    1.391790] CPU: 1 PID: 1 Comm: swapper/0 Not tainted 5.8.13-yocto-standard #1
[    1.392237] NIP:  c0000000008d79f4 LR: c0000000008d9cf8 CTR: c0000000008d7960
[    1.392696] REGS: c0000000723c2f70 TRAP: 0300   Not tainted  (5.8.13-yocto-standard)
[    1.393104] MSR:  9000000002009033 <SF,HV,VEC,EE,ME,IR,DR,RI,LE>  CR: 24000220  XER: 20040000
[    1.393714] CFAR: c0000000008d799c DAR: c00a0000000003e9 DSISR: 40000000 IRQMASK: 1
[    1.393714] GPR00: c0000000008d9cf8 c0000000723c3200 c000000001921f00 c00a0000000003e9
[    1.393714] GPR04: c00a000000000000 00000000000003ef c0000000017ac378 0000000000000000
[    1.393714] GPR08: 0000000000000000 c0000000019cab10 0000000031000040 00000000fffffffe
[    1.393714] GPR12: 0000000000000000 c00000007ffff280 c000000000012190 0000000000000000
[    1.393714] GPR16: 0000000000000000 0000000000000000 0000000000000000 0000000000000000
[    1.393714] GPR20: 0000000000000000 0000000000000000 0000000000000000 0000000000000000
[    1.393714] GPR24: 0000000000000000 c00000000125ad38 c000000001857140 0000000000000000
[    1.393714] GPR28: ffffffffffffffea c000000072d87908 0000000000000001 c000000001adab40
[    1.397765] NIP [c0000000008d79f4] io_serial_in+0x94/0x100
[    1.398104] LR [c0000000008d9cf8] serial8250_config_port+0x3b8/0x1240
[    1.398619] Call Trace:
[    1.398977] [c0000000723c3200] [0000000000000005] 0x5 (unreliable)
[    1.399428] [c0000000723c3230] [c0000000008d9970] serial8250_config_port+0x30/0x1240
[    1.399874] [c0000000723c32d0] [c0000000008d3570] uart_add_one_port+0x250/0x690
[    1.400311] [c0000000723c33e0] [c0000000008d5138] serial8250_register_8250_port+0x368/0x5a0
[    1.400767] [c0000000723c3470] [c0000000008d56fc] serial8250_probe+0x14c/0x1e0
[    1.401194] [c0000000723c37e0] [c000000000995d50] platform_drv_probe+0x60/0xf0
[    1.401603] [c0000000723c3860] [c00000000099208c] really_probe+0x12c/0x580
[    1.401976] [c0000000723c3910] [c000000000992808] driver_probe_device+0x88/0x120
[    1.402373] [c0000000723c3940] [c000000000992d2c] device_driver_attach+0x11c/0x130
[    1.402805] [c0000000723c3980] [c000000000992dec] __driver_attach+0xac/0x190
[    1.403185] [c0000000723c39d0] [c00000000098e868] bus_for_each_dev+0xa8/0x130
[    1.403564] [c0000000723c3a30] [c0000000009914b4] driver_attach+0x34/0x50
[    1.403935] [c0000000723c3a50] [c000000000990bd0] bus_add_driver+0x170/0x2b0
[    1.404329] [c0000000723c3ae0] [c000000000993fd4] driver_register+0xb4/0x1c0
[    1.404690] [c0000000723c3b50] [c000000000995c5c] __platform_driver_register+0x5c/0x70
[    1.405092] [c0000000723c3b70] [c0000000012cbed4] serial8250_init+0x16c/0x1d8
[    1.405454] [c0000000723c3c00] [c000000000011b30] do_one_initcall+0x60/0x2b0
[    1.405828] [c0000000723c3cd0] [c000000001284408] kernel_init_freeable+0x2e0/0x3a4
[    1.406199] [c0000000723c3db0] [c0000000000121b4] kernel_init+0x2c/0x158
[    1.406616] [c0000000723c3e20] [c00000000000d1a8] ret_from_kernel_thread+0x5c/0x74
[    1.407061] Instruction dump:
[    1.407492] 38210030 7fe3fb78 ebe1fff8 4e800020 60000000 60000000 60420000 3d22000b
[    1.407930] 39298c10 e8890000 7c632214 7c0004ac <8be30000> 0c1f0000 4c00012c 57ff063e
[    1.408889] ---[ end trace 57df7bc12c90327a ]---
[    1.409238]
[    2.410095] Kernel panic - not syncing: Attempted to kill init! exitcode=0x0000000b
[   12.174535161,3] Could not set special wakeup on 0:0: timeout waiting for SPECIAL_WKUP_DONE.
[    2.517929] Rebooting in 10 seconds..
```

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
