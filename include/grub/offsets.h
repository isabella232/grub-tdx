/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2002,2003,2007,2008  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER	1

/* The offset of GRUB_TOTAL_MODULE_SIZE.  */
#define GRUB_KERNEL_I386_PC_TOTAL_MODULE_SIZE	0x8

/* The offset of GRUB_KERNEL_IMAGE_SIZE.  */
#define GRUB_KERNEL_I386_PC_KERNEL_IMAGE_SIZE	0xc

/* The offset of GRUB_COMPRESSED_SIZE.  */
#define GRUB_KERNEL_I386_PC_COMPRESSED_SIZE	0x10

/* The offset of GRUB_INSTALL_DOS_PART.  */
#define GRUB_KERNEL_I386_PC_INSTALL_DOS_PART	0x14

/* The offset of GRUB_INSTALL_BSD_PART.  */
#define GRUB_KERNEL_I386_PC_INSTALL_BSD_PART	0x18

/* The offset of GRUB_PREFIX.  */
#define GRUB_KERNEL_I386_PC_PREFIX		0x1c

/* End of the data section. */
#define GRUB_KERNEL_I386_PC_DATA_END		0x5c

/* The size of the first region which won't be compressed.  */
#define GRUB_KERNEL_I386_PC_RAW_SIZE		(GRUB_KERNEL_I386_PC_DATA_END + 0x5F0)

/* The segment where the kernel is loaded.  */
#define GRUB_BOOT_I386_PC_KERNEL_SEG	0x800

/* The upper memory area (starting at 640 kiB).  */
#define GRUB_MEMORY_I386_PC_UPPER		0xa0000
#define GRUB_MEMORY_I386_QEMU_UPPER		GRUB_MEMORY_I386_PC_UPPER

/* The offset of GRUB_CORE_ENTRY_ADDR.  */
#define GRUB_BOOT_I386_QEMU_CORE_ENTRY_ADDR	0x4

/* The offset of GRUB_CORE_ENTRY_ADDR.  */
#define GRUB_KERNEL_I386_QEMU_CORE_ENTRY_ADDR	0x8

/* The offset of GRUB_KERNEL_IMAGE_SIZE.  */
#define GRUB_KERNEL_I386_QEMU_KERNEL_IMAGE_SIZE	0xc

/* The offset of GRUB_PREFIX.  */
#define GRUB_KERNEL_I386_QEMU_PREFIX		0x10

/* End of the data section. */
#define GRUB_KERNEL_I386_QEMU_DATA_END		0x50

#define GRUB_BOOT_SPARC64_IEEE1275_LIST_SIZE	12

#define GRUB_BOOT_SPARC64_IEEE1275_IMAGE_ADDRESS	0x4400

#define GRUB_KERNEL_POWERPC_IEEE1275_PREFIX		0x4
#define GRUB_KERNEL_POWERPC_IEEE1275_DATA_END	0x44
#define GRUB_KERNEL_POWERPC_IEEE1275_LINK_ALIGN 4

#ifdef MACHINE
#define GRUB_OFFSETS_CONCAT_(a,b,c) a ## b ## c
#define GRUB_OFFSETS_CONCAT(a,b,c) GRUB_OFFSETS_CONCAT_(a,b,c)
#define GRUB_KERNEL_MACHINE_TOTAL_MODULE_SIZE GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _TOTAL_MODULE_SIZE)
#define GRUB_KERNEL_MACHINE_KERNEL_IMAGE_SIZE GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _KERNEL_IMAGE_SIZE)
#define GRUB_KERNEL_MACHINE_COMPRESSED_SIZE GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _COMPRESSED_SIZE)

#define GRUB_KERNEL_MACHINE_PREFIX GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _PREFIX)
#define GRUB_KERNEL_MACHINE_DATA_END GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _DATA_END)
#define GRUB_BOOT_MACHINE_KERNEL_SEG GRUB_OFFSETS_CONCAT (GRUB_BOOT_, MACHINE, _KERNEL_SEG)
#define GRUB_MEMORY_MACHINE_UPPER GRUB_OFFSETS_CONCAT (GRUB_MEMORY_, MACHINE, _UPPER)
#define GRUB_KERNEL_MACHINE_RAW_SIZE GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _RAW_SIZE)
#define GRUB_KERNEL_MACHINE_INSTALL_BSD_PART GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _INSTALL_BSD_PART)
#define GRUB_KERNEL_MACHINE_INSTALL_DOS_PART GRUB_OFFSETS_CONCAT (GRUB_KERNEL_, MACHINE, _INSTALL_DOS_PART)
#endif

#ifndef ASM_FILE
struct grub_pc_bios_boot_blocklist
{
  grub_uint64_t start;
  grub_uint16_t len;
  grub_uint16_t segment;
} __attribute__ ((packed));
#endif

#endif
