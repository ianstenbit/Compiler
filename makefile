COMP = main.cpp compiler.cpp line.cpp string.cpp
RUN = test.cpp ifile.cpp ofile.cpp string.cpp

comp :
		g++ $(COMP) -std=c++11 -o Compile

run :
		g++ $(RUN) -std=c++11 -o Run
