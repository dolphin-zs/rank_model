objects = vocab.o rankmodel.o sortrank.o rankmain.o

rankmain : $(objects)
	g++ $(objects) -o rankmain

vocab.o : vocab.cpp vocab.h
	g++ -c vocab.cpp

rankmodel.o : rankmodel.cpp rankmodel.h vocab.h gl_defs.h
	g++ -c rankmodel.cpp

sortrank.o : sortrank.cpp sortrank.h rankmodel.h vocab.h gl_defs.h
	g++ -c sortrank.cpp

rankmain.o : rankmain.cpp sortrank.h rankmodel.h vocab.h gl_defs.h
	g++ -c rankmain.cpp

.PHONY : clean
clean :
	rm -rf rankmain $(objects)

