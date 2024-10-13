CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
main: main.cpp
	g++ $(CXXFLAGS) main.cpp -o main
clean:
	/bin/rm main
