

default: all


all: bin/generator bin/factorisator

run: bin/factorisator
	./bin/factorisator


bin/generator: src/generator.c
	gcc -Wall -std=c99 -o bin/generator src/generator.c -lm -pthread

bin/factorisator: src/main.c
	gcc -Wall -std=c99 src/main.c -o bin/factorisator -lm -pthread

clean:
	rm -f bin/*
