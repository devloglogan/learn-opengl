all:
	mkdir -p build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug && cmake --build .

run: all
	cd build/Debug && ./LearnOpenGL

debug: all
	cd build/Debug && lldb ./LearnOpenGL
