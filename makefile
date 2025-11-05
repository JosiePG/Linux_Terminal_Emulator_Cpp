# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main FileSystemTesterMain

# These are the two executables to be produced
main: src/main.cpp FileSystem.o
	$(CXX) $(CXXFLAGS) src/main.cpp FileSystem.o -o main

FileSystemTesterMain: tests/FileSystemTesterMain.cpp FileSystem.o FileSystemTester.o
	$(CXX) $(CXXFLAGS) tests/FileSystemTesterMain.cpp FileSystem.o FileSystemTester.o -o FileSystemTesterMain

# These are the "intermediate" object files
# The -c command produces them
FileSystem.o: src/FileSystem.cpp src/FileSystem.h
	$(CXX) $(CXXFLAGS) -c src/FileSystem.cpp -o FileSystem.o

FileSystemTester.o: tests/FileSystemTester.cpp tests/FileSystemTester.h src/FileSystem.h
	$(CXX) $(CXXFLAGS) -c tests/FileSystemTester.cpp -o FileSystemTester.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o FileSystemTesterMain main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump
