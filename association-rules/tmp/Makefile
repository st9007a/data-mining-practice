CC=gcc

all:
	$(CC) -o do ./main.c -lm
	$(CC) ./test.c -o debug

run:
	./do

clean:
	rm -f ./do

try:
	./debug

test:
	mv input.txt input.txt.orig
	mv input.txt.test input.txt

reset:
	mv input.txt input.txt.test
	mv input.txt.orig input.txt
