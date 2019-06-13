COMPILER=g++
CFLAGS= -std=c++17 -lm -O1
OBJS=src/main.cpp
WARNINGS= -Wall -Wpedantic -Wshadow
DEBUG= -g -fsanitize=address -fno-omit-frame-pointer
OUTPUT=main
all:
	$(COMPILER) $(OBJS) -o $(OUTPUT) $(CFLAGS) $(WARNINGS) $(DEBUG)
clean:
	rm $(OUTPUT)
