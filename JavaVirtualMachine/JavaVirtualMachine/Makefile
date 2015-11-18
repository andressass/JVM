#############################################################################
# Makefile for building: JVM
#
# Make em sistemas Unix-based $. make all_unix
# Make em sistemas Windows $. make all_win
#
#############################################################################

CC = gcc
STD = -std=c99
CLASS_LOADER_HEADER = include/ClassLoader/**.h
CLASS_LOADER_SOURCES = src/ClassLoader/**.c

ESTRUTURAS_HEADER = include/Estruturas/**.h
ESTRUTURAS_SOURCES = # src/Estruturas/**.c

EXECUTION_ENGINE_HEADER = include/ExecutionEngine/**.h
EXECUTION_ENGINE_SOURCES = src/ExecutionEngine/*.c

MEMORY_UNIT_HEADER = include/MemoryUnit/**.h
MEMORY_UNIT_SOURCES = # src/MemoryUnit/**.c

HEADER = $(CLASS_LOADER_HEADER) $(ESTRUTURAS_HEADER) $(EXECUTION_ENGINE_HEADER) $(MEMORY_UNIT_HEADER)
SOURCES = $(CLASS_LOADER_SOURCES) $(ESTRUTURAS_SOURCES) $(EXECUTION_ENGINE_SOURCES) $(MEMORY_UNIT_SOURCES)
OUT = bin/jvm
OUT_win = bin\jvm.exe
DOXYGEN_CONFIG = docs/doxygen/doxygen_config

all_unix:
	$(CC) $(STD) $(HEADER) $(SOURCES)
	mv a.out $(OUT)
	rm include/*.gch

all_win:
	$(CC) $(STD) $(HEADER) $(SOURCES)


doxygen:

	doxygen  $(DOXYGEN_CONFIG)

