build: clean
	cd ./units/processA && make
	cd ./units/processB && make
clean:
	cd ./units/processA && make clean
	cd ./units/processB && make clean
run: build
	./launch.bat