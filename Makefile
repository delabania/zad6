# make [DEBUG=1] [test]
# make [DEBUG=1] [test/smalltown_test.cc]

SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
TESTS= $(wildcard test/*.cc)

EXEC = horror_movie

CXX = g++
CXXFLAGS = -std=c++14

ifndef DEBUG
CXXFLAGS += -O2
else
CXXFLAGS += -g3 -DDEBUG
endif

all: test

%.o: %.cc
	   $(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TESTS)

%_test.cc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $@ -o $(EXEC)_test
	(./$(EXEC)_test && echo "\033[0;32mTest $@ passed (return code 0)\033[0m") || (echo "\033[0;31mTest $@ failed (return code $$?)\033[0m")

clean:
	rm -f ./*.o ./$(EXEC) ./$(EXEC)_test 2> /dev/null

