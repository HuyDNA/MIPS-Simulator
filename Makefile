SHELL = /bin/bash
.SUFFIXES = .cpp .o

include_paths = ${PWD}

CXX = g++
CXXFLAGS = -I ${include_paths}

.PHONY: all clean test

all:

clean:

test: