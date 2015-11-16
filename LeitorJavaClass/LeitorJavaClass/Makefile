#############################################################################
# Makefile for building: lClass
#
# Make em sistemas Unix-based $. make all_unix
# Make em sistemas Windows $. make all_win
#
#############################################################################

CC = gcc
STD = -std=c99
HEADER = include/**.h
SOURCES = src/**.c
OUT = bin/lclass
OUT_win = bin\lclass.exe
DOXYGEN_CONFIG = docs/doxygen/doxygen_config

all_unix:
	$(CC) $(STD) $(HEADER) $(SOURCES)
	mv a.out $(OUT)
	rm include/*.gch

all_win:
	$(CC) $(STD) $(HEADER) $(SOURCES)


doxygen:

	doxygen  $(DOXYGEN_CONFIG)

