# Makfile for Command-Line Sodoku Game
# Sean Traynor

# Define the compiler
CXX=clang++
CXXFLAGS=-O2 -std=c++11

default: CLSodoku

CLSodoku: main.o SodokuGame.o
	$(CXX) $(CXXFLAGS) -o CLSodoku main.o SodokuGame.o

main.o: main.cpp SodokuGame.h
	$(CXX) $(CXXFLAGS) -c main.cpp

SodokuGame.o: SodokuGame.cpp SodokuGame.h
	$(CXX) $(CXXFLAGS) -c SodokuGame.cpp

clean:
	-@rm -rf *.o 2>/dev/null