all:
	mkdir -p build
	cd build && cmake .. && cmake --build .

run: all
	cd build && ./LearnOpenGL
