.PHONY: all build run clean

all: build run

build:
	cmake -B build
	cmake --build build

run:
	./build/solarsim

clean:
	rm -rf build
