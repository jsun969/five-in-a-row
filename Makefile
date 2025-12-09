build/game: src/main.cpp
	mkdir -p build
	clang++ -std=c++20 -Wall -Wextra src/main.cpp -o build/game