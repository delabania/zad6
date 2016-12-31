# make [DEBUG=1] TEST_FILE=smalltown_test.cc etc.

SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))

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

clean:
	rm ./*.o 2> /dev/null
	rm ./$(EXEC) 2> /dev/null

