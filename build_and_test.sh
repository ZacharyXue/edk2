#!/bin/sh

# https://blog.csdn.net/weixin_41028621/article/details/112546820

# source edksetup.sh

# build -a X64 -p OvmfPkg/OvmfPkgX64.dsc -D DEBUG_ON_SERIAL_PORT

set -e

dd if=/dev/zero of=uefi.img bs=512 count=93750
sgdisk -n 1 -t 1:ef00 -c 1:"EFI System Partition" uefi.img
dd if=/dev/zero of=part.img bs=512 count=91669
mformat -i part.img -h 32 -t 32 -n 64 -c 1
mcopy -i part.img Build/OvmfX64/DEBUG_GCC5/X64/HelloWorld.efi ::
dd if=part.img of=uefi.img bs=512 count=91669 seek=2048 conv=notrunc
sgdisk -p uefi.img

rm start_log.log

#qemu-system-x86_64 -cpu qemu64 -bios /usr/share/ovmf/OVMF.fd -drive file=uefi.img,if=ide -net none
qemu-system-x86_64 -cpu qemu64 -bios Build/OvmfX64/DEBUG_GCC5/FV/OVMF.fd -drive file=uefi.img,\
if=ide -net none -nographic -fw_cfg name=opt/org.tianocore/X-Cpuhp-Bugcheck-Override,string=yes >> start_log.log
