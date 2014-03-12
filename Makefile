

default: all


all: bin/generator bin/factorisator

run: bin/factorisator
	./bin/factorisator


bin/generator: src/generator.c
	gcc -Wall -std=c99 -o bin/generator src/generator.c

bin/factorisator: src/main.c
	gcc -Wall -std=c99 src/main.c -o bin/factorisator

clean:
	rm -f bin/*
