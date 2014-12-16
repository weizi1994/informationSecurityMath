all: field28 sbox

field28: field28.c
	gcc -o field28 field28.c

sbox:
	gcc -o sbox sbox.c

.PHONY: clean
clean:
	rm field28
	rm sbox
