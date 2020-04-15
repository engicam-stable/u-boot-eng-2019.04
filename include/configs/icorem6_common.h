/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright 2018-2019 NXP
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 */

#ifndef __ICOREM6_COMMON_CONFIG_H
#define __ICOREM6_COMMON_CONFIG_H

#include "mx6_common.h"
#include "imx_env.h"

#define CONFIG_IMX_THERMAL
#undef CONFIG_LDO_BYPASS_CHECK
#undef TEE_ENV

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_MXC_UART

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR      0

#define CONFIG_FEC_MXC
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RMII
#ifdef CONFIG_DM_ETH
  #define CONFIG_ETHPRIME			"eth0"
#else
  #define CONFIG_ETHPRIME			"FEC"
#endif

#define CONFIG_FEC_MXC_PHYADDR		1

#define CONFIG_PHY_ATHEROS

#ifdef CONFIG_MX6S
  #define SYS_NOSMP "nosmp"
#else
  #define SYS_NOSMP
#endif

#ifdef CONFIG_NAND_BOOT
  #define MFG_NAND_PARTITION "mtdparts=8000000.nor:1m(boot),-(rootfs)\\;gpmi-nand:64m(nandboot),16m(nandkernel),16m(nanddtb),16m(nandtee),-(nandrootfs)"
#else
  #define MFG_NAND_PARTITION ""
#endif

#define CONFIG_CMD_READ
#define CONFIG_SERIAL_TAG
#define CONFIG_FASTBOOT_USB_DEV 0

#define CONFIG_MFG_ENV_SETTINGS \
	"initrd_addr=0x12C00000\0" \
	"initrd_high=0xffffffff\0" \
  "fdt_high=0xffffffff\0"	  \
  "fdt_addr=0x18000000\0" \
  "console=" CONSOLE_DEV "\0" \
  "mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
  "mmcpart=1\0" \
  "lcd_panel=Amp-WD\0" 			\
  "video_type=mxcfb0:dev=lcd\0"

#ifdef CONFIG_MX6S
  #define EXTRA_OPTION_SOLO	 " cma=128MB "
#else
  #define EXTRA_OPTION_SOLO ""
#endif

#define LOAD_BOOT  "run loadfdt; run loadimage; bootm ${loadaddr} - ${fdt_addr}" 
#define CONFIG_LOAD_IMAGE	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} uImage\0" 
#define CONFIG_LOAD_FDT	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" 
#define CONFIG_BOOTARGS_BASE "bootargs_base=setenv bootargs_tmp console=" CONSOLE_DEV ",115200 " EXTRA_OPTION_SOLO " video=${video_type},${lcd_panel}\0" 
#define CONFIG_BOOTARGS_MMC  "bootargs_mmc=run bootargs_base; setenv bootargs ${bootargs_tmp} ${mtdparts} root=/dev/mmcblk${mmcdev}p2 rootwait rw\0" 
#define CONFIG_BOOTARGS_NET  "bootargs_net=run bootargs_base; setenv bootargs ${bootargs_tmp} root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" 
#define CONFIG_BOOTCMD_MMC	 "bootcmd_mmc=setenv mmcdev ${mmcdev}; run bootargs_mmc; " LOAD_BOOT "\0" 
#define CONFIG_BOOTCMD_NET	 "bootcmd_net=run bootargs_net; tftp uImage; tftp ${fdt_addr} uImage.dtb; bootm ${loadaddr} - ${fdt_addr}\0" 

#define COMMON_PARAMETER 	""

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#if defined(CONFIG_NAND_BOOT) /* TODO */

#elif defined(CONFIG_SATA_BOOT) /* TODO */

#else
#define CONFIG_EXTRA_ENV_SETTINGS \
  CONFIG_BOOTARGS_BASE \
  CONFIG_BOOTARGS_MMC \
  CONFIG_BOOTARGS_NET \
  CONFIG_LOAD_IMAGE \
  CONFIG_LOAD_FDT \
  CONFIG_BOOTCMD_MMC \
  CONFIG_BOOTCMD_NET \
	CONFIG_MFG_ENV_SETTINGS \
	"bootcmd=run bootcmd_mmc\0"\
	"fdt_file=icoremx6dl-starterkit-cap.dtb\0"
#endif

#define CONFIG_ARP_TIMEOUT     200UL

#define CONFIG_SYS_MEMTEST_START       0x10000000
#define CONFIG_SYS_MEMTEST_END         0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH     0x10800000

/* Physical Memory Map */
#define PHYS_SDRAM                     MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE          PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_SIZE			(8 * 1024)

#ifdef CONFIG_MTD_NOR_FLASH
  #define CONFIG_SYS_FLASH_BASE           WEIM_ARB_BASE_ADDR
  #define CONFIG_SYS_FLASH_SECT_SIZE      (128 * 1024)
  #define CONFIG_SYS_MAX_FLASH_BANKS 1    /* max number of memory banks */
  #define CONFIG_SYS_MAX_FLASH_SECT 256   /* max number of sectors on one chip */
  #define CONFIG_SYS_FLASH_CFI            /* Flash memory is CFI compliant */
  #define CONFIG_SYS_FLASH_USE_BUFFER_WRITE /* Use buffered writes*/
  #define CONFIG_SYS_FLASH_EMPTY_INFO
  #define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#endif

#ifdef CONFIG_NAND_MXS

  #define CONFIG_SYS_MAX_NAND_DEVICE     1
  #define CONFIG_SYS_NAND_BASE           0x40000000
  #define CONFIG_SYS_NAND_5_ADDR_CYCLE
  #define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#endif

#if defined(CONFIG_ENV_IS_IN_MMC)
  #define CONFIG_ENV_OFFSET		(896 * 1024)
#elif defined(CONFIG_ENV_IS_IN_SPI_FLASH)
  #define CONFIG_ENV_OFFSET              (896 * 1024)
  #define CONFIG_ENV_SECT_SIZE           (64 * 1024)
  #define CONFIG_ENV_SPI_BUS             CONFIG_SF_DEFAULT_BUS
  #define CONFIG_ENV_SPI_CS              CONFIG_SF_DEFAULT_CS
  #define CONFIG_ENV_SPI_MODE            CONFIG_SF_DEFAULT_MODE
  #define CONFIG_ENV_SPI_MAX_HZ          CONFIG_SF_DEFAULT_SPEED
#elif defined(CONFIG_ENV_IS_IN_FLASH)
  #undef CONFIG_ENV_SIZE
  #define CONFIG_ENV_SIZE                        CONFIG_SYS_FLASH_SECT_SIZE
  #define CONFIG_ENV_SECT_SIZE           CONFIG_SYS_FLASH_SECT_SIZE
  #define CONFIG_ENV_OFFSET              (7 * CONFIG_SYS_FLASH_SECT_SIZE)
#elif defined(CONFIG_ENV_IS_IN_NAND)
  #undef CONFIG_ENV_SIZE
  #define CONFIG_ENV_OFFSET              (60 << 20)
  #define CONFIG_ENV_SECT_SIZE           (128 << 10)
  #define CONFIG_ENV_SIZE                        CONFIG_ENV_SECT_SIZE
#elif defined(CONFIG_ENV_IS_IN_SATA)
  #define CONFIG_ENV_OFFSET		(896 * 1024)
  #define CONFIG_SYS_SATA_ENV_DEV		0
#endif

/* I2C Configs */
#ifndef CONFIG_DM_I2C
  #define CONFIG_SYS_I2C
#endif
#ifdef CONFIG_CMD_I2C
  #define CONFIG_SYS_I2C_MXC
  #define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
  #define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
  #define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
  #define CONFIG_SYS_I2C_SPEED		  100000
#endif

#if defined(CONFIG_ANDROID_SUPPORT)
  #include "mx6sabreandroid_common.h"
#else
  #define CONFIG_USBD_HS
#endif /* CONFIG_ANDROID_SUPPORT */

#endif                         /* __ICOREM6_COMMON_CONFIG_H */
