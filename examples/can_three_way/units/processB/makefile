LIB ?= $(KLNEXUS_PATH)/lib
INCLUDE ?= $(KLNEXUS_PATH)/include
SHARED ?= ../../shared
UNIT_NAME ?= b

build: clean $(UNIT_NAME).exe clean_artifacts

$(UNIT_NAME).exe: $(UNIT_NAME).o
	gcc -L$(LIB) -lnexus $(UNIT_NAME).o -o $(UNIT_NAME).exe

$(UNIT_NAME).o: $(UNIT_NAME).c
	gcc -I$(INCLUDE) -I$(SHARED) -c $(UNIT_NAME).c -o $(UNIT_NAME).o

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.exe
	rm -f *.o
    