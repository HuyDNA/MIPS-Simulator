SHELL 			 = /bin/bash
.SUFFIXES 		 = .cpp .o

program_name	:= MIPS_Simulator
precompile_cache:= .cached
source_files 	:= $(shell find . -type f -name "*.cpp" -not -path "./TestSuite/*")
header_files	:= $(shell find . -type f -name "*.h" -not -path "./TestSuite/*")
test_files 		:= $(shell find "./TestSuite" -name "*.cpp")
include_paths 	:= ${PWD}

CXX 			 = g++
CXXFLAGS 		 = -I ${include_paths} -std=c++20

_red_			:= \e[31m
_magenta_		:= \e[35m
_green_			:= \e[32m
_white_			:= \e[97m
_cyan_			:= \e[36m

.PHONY : all clean test

all:

precompile: .cached

.cached: ${source_files} ${header_files}
	@echo -e "${_magenta_}Precompiling..."; \
		echo -e -n "${_cyan_}"; \
		ls ${precompile_cache} > /dev/null 2>&1 || mkdir ${precompile_cache}; \
		cd ${precompile_cache} && ${CXX} ${CXXFLAGS} -c $(patsubst ./%,../%,${source_files})

clean:
	@echo -e "${_magenta_}Cleaning..."
	@rm -rf .cached ${program_name}

test: precompile
	@echo -e "${_white_}Initiating test...\n"

	@for test in ${test_files}; do \
		echo -e "${_magenta_}Testing $${test##*/}..."; \
		make -s $${test%.*}; \
		echo -e -n "${_cyan_}"; \
		${CXX} ${CXXFLAGS} -o test ${precompile_cache}/* $$test && ./test; \
		if [ "$$?" -eq 0 ]; then \
			echo -e "${_green_}Passed all tests in $${test##*/}\n"; \
		else \
			echo -e "${_red_}Failed!\n"; \
		fi; \
	done; \
	echo -e "${_white_}Cleaning after tests..."; \
	rm -rf test $$(find "./TestSuite/" -type f -executable); \
	echo -e "ALL DONE!"