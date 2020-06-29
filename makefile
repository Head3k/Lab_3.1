all:bin/coder

bin/coder:src/main.c
	gcc -Wall -I src src/main.c  src/varint.c -o bin/coder -lm
run:
	./bin/coder
	
clean:
	rm -rf build/*.bin 
	rm -rf bin/coder
