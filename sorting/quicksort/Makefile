# Makefile

# Compiler to use
CXX ?= c++

# Flags to pass to compiler
CXXFLAGS ?= -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 \
			-O0 -Qunused-arguments -std=c++17 -Wall -Werror -Wextra \
			-Wno-sign-compare -Wno-unused-parameter

# Name for executable
EXE = quicksort

# Space separated list of header-files
HDRS = quicksort.hh pivots.hh randomize_array.hh

# Space separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# Space separated list of source-files
SRCS = main.cc quicksort.cc pivots.cc randomize_array.cc

# Automatically generated list of object files
OBJS = $(SRCS:.cc=.o)

.PHONY: all
all: $(EXE)

# Default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

# Dependencies
$(OBJS): $(HDRS) Makefile

.PHONY: clean
clean:
	rm -f core $(EXE) *.o

