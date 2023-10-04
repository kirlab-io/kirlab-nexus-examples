ifeq ($(OS),Windows_NT)
    EXE_EXT = .exe
else
    EXE_EXT =
endif

LIB ?= $(KLNEXUS_PATH)/lib
INCLUDE ?= $(KLNEXUS_PATH)/include
SHARED ?= ../../shared
UNIT_NAME ?= a
CXXFLAGS = -Wall -O3

build: clean $(UNIT_NAME)$(EXE_EXT) clean_artifacts

$(UNIT_NAME)$(EXE_EXT): $(UNIT_NAME).o
	gcc $(CXXFLAGS) -L$(LIB) -lnexus $(UNIT_NAME).o -o $(UNIT_NAME)$(EXE_EXT)

$(UNIT_NAME).o: $(UNIT_NAME).c
	gcc $(CXXFLAGS) -I$(INCLUDE) -I$(SHARED) -c $(UNIT_NAME).c -o $(UNIT_NAME).o

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.exe
	rm -f $(UNIT_NAME)
	rm -f *.o
    