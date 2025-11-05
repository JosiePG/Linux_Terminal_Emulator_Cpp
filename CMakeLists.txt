cmake_minimum_required(VERSION 4.0)
project(Cpp_UniCourseWork)

set(CMAKE_CXX_STANDARD 17)

# ---- Main program ----
add_executable(Cpp_UniCourseWork
        src/main.cpp
        src/FileSystem.cpp
        src/FileSystem.h
)

# ---- Test program ----
add_executable(Cpp_UniCourseWork_Tests
        tests/FileSystemTesterMain.cpp
        tests/FileSystemTester.cpp
        tests/FileSystemTester.h
        src/FileSystem.cpp   # shared code
)
