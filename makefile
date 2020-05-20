all:bin/main


bin/main:build/src/main.o 
	gcc -Wall build/src/main.o -o bin/main
build/src/main.o:src/main.c
	gcc -Wall -c src/main.c -o build/src/main.o


run:
	bin/./main


clean:
	rm -rf build/src/*.o bin/main build/*.dat
