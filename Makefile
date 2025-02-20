all: build run

build:
	cmake -S . -B build
	cmake --build build

run: build
	./build/main

clean:
	@rm -rf build
	@echo "Removed build files"
