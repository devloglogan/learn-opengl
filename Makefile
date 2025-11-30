all:
	mkdir -p build
	cd build && cmake .. && cmake --build .

run:
	cd build && ./LearnOpenGL
