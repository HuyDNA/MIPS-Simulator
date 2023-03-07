SHELL 			 = /bin/bash
.SUFFIXES 		 = .cpp .o

source_files 	:= $(shell find . -name "*.cpp" -not -path "./TestSuite/*")
test_files 		:= $(shell find "./TestSuite" -name "*.cpp")
include_paths 	:= ${PWD}

CXX 			 = g++
CXXFLAGS 		 = -I ${include_paths}

.PHONY	: all clean test

all		:

clean	:

test	:
	for test in ${test_files}; do \
		${CXX} ${CXXFLAGS} -o test ${source_files} $$test && ./test; \
	done