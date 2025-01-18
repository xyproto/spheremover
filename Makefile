.PHONY: all clean run

all: build/spheremover

build/spheremover: build
	make -C build

build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

run: build/spheremover
	./build/spheremover

clean:
	rm -rf build/