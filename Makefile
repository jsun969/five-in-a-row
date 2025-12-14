SRCS = $(wildcard src/*.cpp)
HEADS = $(wildcard src/*.hpp)

build/game: $(SRCS) $(HEADS)
	mkdir -p build
	clang++ -std=c++20 -Wall -Wextra $(SRCS) -o build/game