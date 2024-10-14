CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
main: src/main.cpp
	g++ $(CXXFLAGS) src/main.cpp -o main
clean:
	/bin/rm main
	/bin/rm -r main.dSYM
