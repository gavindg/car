CXXFLAGS=-ggdb -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic
INCLUDE_PATH=include/
main: src/main.cpp src/pipeline.cpp src/transformations.cpp include/Models.h
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/main.cpp src/pipeline.cpp src/transformations.cpp src/shade.cpp -o cpr
tests: src/tests.cpp src/pipeline.cpp include/Matrix.h src/transformations.cpp include/vector.h include/Triangle.h
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/tests.cpp src/pipeline.cpp src/transformations.cpp src/shade.cpp -o tests
clean:
	/bin/rm cpr
	/bin/rm -r cpr.dSYM
