# Copyright (C) 2023 Kirlab
#
# This file is part of KirLab Nexus.
#
# This file cannot be copied and/or distributed without the express
# permission of Kirlab.

.PHONY: all nl5 psim clean_artifacts clean help

SRC ?= dll.c
OUT_DIR ?= .
LIB ?= $(KLNEXUS_PATH)/lib
INCLUDE ?= $(KLNEXUS_PATH)/include
SHARED ?= ../../shared

help:
	@echo "Makefile usage:"
	@echo "  make all            - build plecs.dll, psim.dll and nl5.dll"
	@echo "  make nl5            - build nl5.dll"
	@echo "  make psim           - build psim.dll"
	@echo "  make plecs          - build plecs.dll"
	@echo "  make clean          - remove all .dll and .o files"
	@echo "To specify a different source file, use the SRC variable:"
	@echo "  make SRC=your_source_file.c"
	@echo "To specify a different output directory, use the OUT_DIR variable:"
	@echo "  make OUT_DIR=your_output_directory"

all: clean plecs.dll nl5.dll psim.dll clean_artifacts

nl5: clean nl5.dll clean_artifacts

psim: clean psim.dll clean_artifacts

plecs: clean plecs.dll clean_artifacts

nl5.dll: $(SRC:.c=.o)
	gcc -shared -L$(LIB) -lnexus_nl5 -lnexus $(SRC:.c=.o) -o $(OUT_DIR)/nl5.dll

psim.dll: $(SRC:.c=.o)
	gcc -shared -L$(LIB) -lnexus_psim -lnexus $(SRC:.c=.o) -o $(OUT_DIR)/psim.dll

plecs.dll: $(SRC:.c=.o)
	gcc -shared -L$(LIB) -lnexus_plecs -lnexus $(SRC:.c=.o) -o $(OUT_DIR)/plecs.dll

$(SRC:.c=.o): $(SRC)
	gcc -I$(INCLUDE) -I$(SHARED) -c $(SRC) -o $(SRC:.c=.o)

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.dll
	rm -f *.o
