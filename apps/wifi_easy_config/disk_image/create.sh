#!/bin/bash

# Creating a binary file with the exact size of 70*512 = 35840 and content are just zero’s
dd if=/dev/zero of=disk.img bs=512 count=256

# The standard Linux tool “mkfs” put’s into this zeroed file, a DOS file system with a FAT12
mkfs.msdos -F 12 disk.img

# mcopy put a file into the disk image without mounting the image
mcopy -i disk.img ./web_pages/* ::

# mdir is listing the content of the image
mdir -/ -i disk.img ::

# xxd converts the image into a C const array
xxd -i disk.img >vfat.c

