@echo off
pushd %cd%
cd src
make iso
qemu-system-i386 -cdrom os.iso -serial file:..\serial1.log
make clean
popd