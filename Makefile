COMPILER = g++-7
STD = -std=c++17
PARALLEL = -pthread
EXE = ./a.out
MODELSPATH = MODELS/
MODELS = $(MODELSPATH)LinearRegression.hpp
FILES = Standerd.hpp Type.hpp Cast.hpp Tools.hpp Math.hpp Matrix.hpp MLKit.hpp Linkedlist.hpp $(MODELS) main.cpp

all:
		$(COMPILER) $(STD) $(PARALLEL) $(FILES)
		$(EXE)

compile:
		$(COMPILER) $(STD) $(PARALLEL) $(FILES)

run:
		$(EXE)
