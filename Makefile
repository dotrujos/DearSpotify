all:
	cmake -S . -B build
	cmake --build build
	./build/DearSpotify

clean:
	rm -rf build