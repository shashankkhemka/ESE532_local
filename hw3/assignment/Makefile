CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -g -DNDEBUG -pthread
LDFLAGS = -lpthread -pthread
INCLUDES = -I./common

EXECUTABLES = base coarse pipeline2 cdc walkthrough
BASELINE_SRC = $(wildcard baseline/*.cpp common/*.cpp)
COURSEGRAIN_SRC = $(wildcard coarse_grain/*.cpp common/*.cpp)
PIPELINE2_SRC = $(wildcard pipeline_2_cores/*.cpp common/*.cpp)
CDC_SRC = $(wildcard cdc_parallel/*.cpp common/*.cpp)
WALKTHROUGH_SRC = Walkthrough.cpp $(wildcard common/*.cpp)

.PHONY: clean

all: $(EXECUTABLES)
	@echo $(EXECUTABLES) compiled!

base: $(BASELINE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

coarse: $(COURSEGRAIN_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

pipeline2: $(PIPELINE2_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

cdc: $(CDC_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

walkthrough: $(WALKTHROUGH_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -rf perf* *.bin *.txt *.dSYM *.out *.o *~ $(EXECUTABLES)
