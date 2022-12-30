all:
	make build
	make run

build: main.c test.asm
	gcc main.c -o lvm
	nasm test.asm -f bin -o test.bin

run: lvm test.bin
	./lvm test.bin