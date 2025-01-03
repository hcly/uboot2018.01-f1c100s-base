/*
 * Copyright 2014 Broadcom Corporation.
 * Copyright 2015 Free Electrons.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

void fb_spinand_flash_write(const char *cmd, void *download_buffer,
			 unsigned int download_bytes);
void fb_spinand_erase(const char *cmd);
