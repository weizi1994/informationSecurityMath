all: field28 sbox

field28: field28.c field28.h
	gcc -o field28 field28.c

sbox: sbox.c sbox.h
	gcc -o sbox sbox.c

.PHONY: clean
clean:
	rm field28
	rm sbox
