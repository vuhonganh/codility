CXX = g++
GCC = GCC
CC  = g++
LD  = g++
CXXFLAGS = -Wall -Wextra -Werror -g -lm -std=c++11

SRCS = $(wildcard *.cpp)

exe = main

all: $(exe)

run: $(exe)
	./$<

clean: 
	rm -rf $(exe)
