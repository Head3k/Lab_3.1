all:main


main:build/src/main.o
	gcc -Wall build/src/main.o -o main
build/src/main.o:src/main.c
	gcc -Wall -c src/main.c -o build/src/main.o

clean:
	rm -rf build/src/*.o bin/main build/*.dat
