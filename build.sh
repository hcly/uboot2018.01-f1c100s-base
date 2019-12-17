#!/bin/bash
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- licheepi_nano_spinand_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8
if [ -f u-boot-sunxi-with-spl.bin ]; then
	./f1c100_uboot_spinand.sh uboot-with-spl-spinand.bin u-boot-sunxi-with-spl.bin
	echo "burn uboot-with-spl-spinand.bin to spi nand"
	echo "cmd is sunxi-fel uboot u-boot-sunxi-with-spl.bin write 0x80000000 uboot-with-spl-spinand.bin"
else
	echo "ERROR"
fi
echo "DONE"

