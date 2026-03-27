all:
	mkdir -p build
	cd build && cmake .. && cmake --build .

run:
	./build/Debug/LearnOpenGL
