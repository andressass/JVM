#############################################################################
# Makefile for building: lClass
#############################################################################

CC = gcc
STD = -std=c99
HEADER = include/**.h
SOURCES = src/**.c
OUT = bin/lclass
DOXYGEN_CONFIG = docs/doxygen/doxygen_config

all:
	$(CC) $(STD) $(HEADER) $(SOURCES)
	mv a.out $(OUT)
	rm include/*.gch

doxygen:

	doxygen  $(DOXYGEN_CONFIG)

