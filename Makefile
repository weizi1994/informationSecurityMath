FLAGS=-Ofast

all: field28 sbox

field28: field28.c field28.h
	gcc $(FLAGS) -o field28 field28.c

sbox: sbox.c sbox.h
	gcc $(FLAGS) -o sbox sbox.c

.PHONY: clean
clean:
	rm field28
	rm sbox
