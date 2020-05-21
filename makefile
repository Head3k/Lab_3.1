all:bin/main

bin/main:src/main.c
	gcc -Wall -I src src/main.c src/varint.c -o bin/main

run:
	bin/./main


clean:
	rm -rf build/src/*.o bin/main build/*.bin
