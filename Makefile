.PHONY: all build run clean

all: build run

build:
	cmake -B build
	cmake --build build

run:
ifeq ($(OS),Windows_NT)
	build\Debug\solarsim.exe
else
	./build/solarsim
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q build
else
	rm -rf build
endif
