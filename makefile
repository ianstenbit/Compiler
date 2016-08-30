COMP = main.cpp compiler.cpp line.cpp string.cpp
INDEX = AutoIndexer.cpp ifile.cpp ofile.cpp string.cpp
FOREACH = AutoIndexer.cpp ifile.cpp ofile.cpp string.cpp
TEST = test.cpp ifile.cpp ofile.cpp string.cpp

compiler :
		g++ $(COMP) -std=c++11 -o Compiler

indexer :
		./Compiler AutoIndexer.spp
		g++ $(INDEX) -std=c++11 -o Indexer

foreach :
		./Compiler ForEach.spp
		g++ $(FOREACH) -std=c++11 -o ForEach

test :
		g++ $(TEST) -std=c++11 -o Test
