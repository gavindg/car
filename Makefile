CXXFLAGS=-ggdb -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic
INCLUDE_PATH=include/
main: src/main.cpp
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/main.cpp -o cpr
tests: src/tests.cpp
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/tests.cpp -o tests
clean:
	/bin/rm main
	/bin/rm -r main.dSYM
