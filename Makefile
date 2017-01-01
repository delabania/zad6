# make [DEBUG=1] TEST_FILE=smalltown_test.cc etc.

SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
TESTS= $(wildcard test/*.cc)

EXEC = horror_movie

CXX = g++
CXXFLAGS = -std=c++14

ifndef DEBUG
CXXFLAGS += -O2
else
CXXFLAGS += -g3
endif

ifndef TEST_FILE
TEST_FILE = monster_test.cc
endif

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) ./test/$(TEST_FILE) -o $(EXEC)

%.o: %.cc
	   $(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TESTS)

%_test.cc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $@ -o $(EXEC)_test
	(./$(EXEC)_test && echo "\033[0;32mTest $@ passed (return code 0)\033[0m") || (echo "\033[0;31mTest $@ failed (return code $$?)\033[0m")

clean:
	rm -f ./*.o ./$(EXEC) ./$(EXEC)_test 2> /dev/null

