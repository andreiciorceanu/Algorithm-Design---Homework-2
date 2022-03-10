CC=g++
CFLAGS=-Wall -Wextra -m32 -Wpedantic

build:
	g++ poduri.cpp -o poduri
	gcc adrese.c -o adrese
	gcc lego.c -o lego
	g++ retea.cpp -o retea

run-p1:
	./poduri
run-p2:
	./adrese
run-p3:
	./lego
run-p4:
	./retea

clean:
	rm -rf poduri adrese lego retea
