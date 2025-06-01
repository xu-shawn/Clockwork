SOURCES := src/main.cpp src/uci.cpp

CXX ?= g++
ENV_CXXFLAGS := $(CXXFLAGS)
CXXFLAGS := $(ENV_CXXFLAGS) -std=c++17 -O3 -flto -fno-exceptions -fno-rtti
EXE ?= clockwork

ifeq ($(OS), Windows_NT)
    SUFFIX := .exe
else
    SUFFIX :=
endif

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXE)
