/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2026 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 * Generated linker script file for MCXC162
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v25.6 [Build 136] [2025-06-27] on Jul 22, 2026, 3:56:10 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64K bytes (alias Flash) */  
  DATA_FLASH (rx) : ORIGIN = 0x1c000, LENGTH = 0x4000 /* 16K bytes (alias Flash2) */  
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x3000 /* 12K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x10000 ; /* 64K bytes */  
  __top_Flash = 0x0 + 0x10000 ; /* 64K bytes */  
  __base_DATA_FLASH = 0x1c000  ; /* DATA_FLASH */  
  __base_Flash2 = 0x1c000 ; /* Flash2 */  
  __top_DATA_FLASH = 0x1c000 + 0x4000 ; /* 16K bytes */  
  __top_Flash2 = 0x1c000 + 0x4000 ; /* 16K bytes */  
  __base_SRAM = 0x20000000  ; /* SRAM */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM = 0x20000000 + 0x3000 ; /* 12K bytes */  
  __top_RAM = 0x20000000 + 0x3000 ; /* 12K bytes */  
