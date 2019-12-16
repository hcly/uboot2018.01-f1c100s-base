#!/bin/bash
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- licheepi_nano_spinand_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8

