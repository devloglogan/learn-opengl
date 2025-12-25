cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(thirdparty/cglm)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
  cglm
  glad
  glfw
)
