COMP = main.cpp compiler.cpp line.cpp string.cpp
RUN = AutoIndexer.cpp ifile.cpp ofile.cpp string.cpp

comp :
		g++ $(COMP) -std=c++11 -o Compile

run :
		./Compile AutoIndexer.spp
		g++ $(RUN) -std=c++11 -o Run
