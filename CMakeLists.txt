project(word-counter)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
add_executable(${PROJECT_NAME} word-counter.cpp)