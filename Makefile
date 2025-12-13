SRCS = $(wildcard src/*.cpp)

build/game: $(SRCS)
	mkdir -p build
	clang++ -std=c++20 -Wall -Wextra $(SRCS) -o build/game