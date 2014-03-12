

default: all


all: bin/generator bin/factorisator

run: bin/factorisator
	./bin/factorisator


bin/generator: src/generator.c
	gcc -Wall -o bin/generator src/generator.c

bin/factorisator: src/main.c
	gcc -Wall src/main.c -o bin/factorisator

clean:
	rm -f bin/*
