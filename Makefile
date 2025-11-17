.PHONY: all build run clean

all: build run

build:
	cmake -B build
	cmake --build build --target solarsim

run:
ifeq ($(OS),Windows_NT)
	build\Debug\solarsim.exe
else
	./build/solarsim
endif

test: build
ifeq ($(OS),Windows_NT)
	cd build && cmake --build . --target solarsim_tests && ctest -C Debug
else
	cd build && cmake --build . --target solarsim_tests && ctest --output-on-failure
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q build
else
	rm -rf build
endif
