LIB ?= $(KLNEXUS_PATH)/lib
SHARED ?= ../../shared
UNIT_NAME ?= b

build: clean $(UNIT_NAME).exe clean_artifacts

$(UNIT_NAME).exe: $(UNIT_NAME).o
	gcc $(UNIT_NAME).o -L$(LIB) -lnexus -lnexuscom -o $(UNIT_NAME).exe

$(UNIT_NAME).o: $(UNIT_NAME).c
	gcc -I$(LIB) -I$(SHARED) -c $(UNIT_NAME).c -o $(UNIT_NAME).o

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.exe
	rm -f *.o
    