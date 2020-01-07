/*
 * Copyright 2014 Broadcom Corporation.
 * Copyright 2015 Free Electrons.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>

#include <fastboot.h>

static int strcmp_l1(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return -1;
	return strncmp(s1, s2, strlen(s1));
}

void fb_spinand_flash_write(const char *cmd, void *download_buffer,
			 unsigned int download_bytes)
{
	int ret;
	int size;
	char cmd_buf[200];
	if (!strcmp_l1(cmd, "uboot")) {
		printf("write uboot to spinand\n");
		sprintf(cmd_buf, "spi_nand update 0x%x 0 0x200000",CONFIG_FASTBOOT_BUF_ADDR);
		printf("cmd_buf:%s\n",cmd_buf);
	} else if(!strcmp_l1(cmd, "logo")) {
		printf("write logo to spinand\n");
		sprintf(cmd_buf, "spi_nand update 0x%x 0x200000 0x200000",CONFIG_FASTBOOT_BUF_ADDR);
		printf("cmd_buf:%s\n",cmd_buf);
	} else if(!strcmp_l1(cmd, "zImage")) {
		printf("write zImage to spinand\n");
		sprintf(cmd_buf, "spi_nand update 0x%x 0x400000 0x500000",CONFIG_FASTBOOT_BUF_ADDR);
		printf("cmd_buf:%s\n",cmd_buf);
	} else if(!strcmp_l1(cmd, "dtb")) {
		printf("write dtb to spinand\n");
		sprintf(cmd_buf, "spi_nand update 0x%x 0x900000 0x20000",CONFIG_FASTBOOT_BUF_ADDR);
		printf("cmd_buf:%s\n",cmd_buf);
	} else if(!strcmp_l1(cmd, "rootfs")) {
		printf("write rootfs to spinand download_bytes:%d first erase rootfs\n",download_bytes);
		run_command("spi_nand erase 0x920000 0x76e0000",0);
		size = download_bytes/(128*1024);
		if(download_bytes/(128*1024) != 0)
			size += 1;
		if(size == 0)
			size = 1;
		size = size * 128 * 1024;
		sprintf(cmd_buf, "spi_nand write 0x%x 0x920000 0x%x",CONFIG_FASTBOOT_BUF_ADDR,size);
		printf("cmd_buf:%s\n",cmd_buf);
	} else {
		fastboot_fail("Unkown Command");
		return;
	}
	ret = run_command(cmd_buf,0);
	if (ret) {
		pr_err("spi nand update failed\n");
		fastboot_fail("*********spi nand update failed**********");
		return;
	}
	fastboot_okay("");
}

void fb_spinand_erase(const char *cmd)
{
	int ret;
	ret = run_command("spi_nand erase 0 0x8000000",0);
	if (ret) {
		pr_err("spi nand erase failed\n");
		fastboot_fail("*********spi nand erase failed**********");
		return;
	}
	fastboot_okay("");
}
