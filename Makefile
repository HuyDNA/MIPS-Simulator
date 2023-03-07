SHELL 			 = /bin/bash
.SUFFIXES 		 = .cpp .o

source_files 	:= $(shell find . -name "*.cpp" -not -path "./TestSuite/*")
test_files 		:= $(shell find "./TestSuite" -name "*.cpp")
include_paths 	:= ${PWD}

CXX 			 = g++
CXXFLAGS 		 = -I ${include_paths} -std=c++20

_red_			:= \e[31m
_magenta_		:= \e[35m
_green_			:= \e[32m
_white_			:= \e[97m
_cyan_			:= \e[36m

.PHONY	: all clean test

all		:

clean	:

test	:
	@echo -e "${_white_}Initiating test...\n"

	@for test in ${test_files}; do \
		echo -e "${_magenta_}Testing $${test##*/}..."; \
		echo -e -n "${_red_}"; \
		${CXX} ${CXXFLAGS} -o test ${source_files} $$test && ./test; \
		if [ "$$?" -eq 0 ]; then \
			echo -e "${_green_}Passed all tests in $${test##*/}\n"; \
		else \
			echo -e "${_red_}Failed!"; \
		fi; \
	done; \
	echo -e "${_white_}Cleaning after tests..."; \
	rm test; \
	echo -e "ALL DONE!"; \