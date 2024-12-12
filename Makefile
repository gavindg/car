CXXFLAGS=-ggdb -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic
INCLUDE_PATH=include/
main: src/main_unix.cpp src/pipeline.cpp src/transformations.cpp include/Models.h
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/main_unix.cpp src/pipeline.cpp src/transformations.cpp src/shade.cpp -o car
win: src/main_win.cpp src/pipeline.cpp src/transformations.cpp include/Models.h
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/main_win.cpp src/pipeline.cpp src/transformations.cpp src/shade.cpp -o car
tests: src/tests.cpp src/pipeline.cpp include/Matrix.h src/transformations.cpp include/vector.h include/Triangle.h
	g++ $(CXXFLAGS) -I$(INCLUDE_PATH) src/tests.cpp src/pipeline.cpp src/transformations.cpp src/shade.cpp -o tests
