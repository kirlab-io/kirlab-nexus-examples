LIB ?= $(KLNEXUS_PATH)/lib
SHARED ?= ../../shared
UNIT_NAME ?= signal_generator

build: clean $(UNIT_NAME).exe clean_artifacts

$(UNIT_NAME).exe: $(UNIT_NAME).o
	gcc -L$(LIB) -lnexus $(UNIT_NAME).o -o $(UNIT_NAME).exe

$(UNIT_NAME).o: $(UNIT_NAME).c
	gcc -I$(LIB) -I$(SHARED) -c $(UNIT_NAME).c -o $(UNIT_NAME).o

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.exe
	rm -f *.o
    