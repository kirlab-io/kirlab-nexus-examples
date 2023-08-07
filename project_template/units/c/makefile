build: clean main.exe clean_artifacts

LIB ?= $(KLNEXUS_PATH)/lib
SHARED ?= ../../shared

main.exe: main.o
	gcc -L$(LIB) -lnexus main.o -o main.exe

main.o: main.c
	gcc -I$(LIB) -I$(SHARED) -c main.c -o main.o

clean_artifacts:
	rm -f *.o

clean:
	rm -f *.exe
	rm -f *.o
    