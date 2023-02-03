######################################################################
#  Project Makefile
######################################################################
LIBOPENCM3 = 1
FREERTOS = 1
BOARD = STM32F103C8

BINARY		= src/main
SRCFILES	= src/main.c
FREERTOS_OBJS = list.o tasks.o queue.o
LIB_OBJS = opencm3_serial.o
FREERTOS_MEM = heap_4.o

include ../Makefile.incl


######################################################################
#  NOTES:
#
#	1. remove any modules you don't need from SRCFILES
#	2. "make clean" will remove *.o etc., but leaves *.elf, *.bin
#	3. "make clobber" will "clean" and remove *.elf, *.bin etc.
#	4. "make flash" will perform:
#	   st-flash write main.bin 0x8000000
#
######################################################################
