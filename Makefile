objects1 = vocab.o rankmodel.o buildrank.o rankmain.o
objects2 = vocab.o sentence.o model12.o sortmodel1.o model1main.o
objects3 = vocab.o rankmodel.o buildrank.o multimain.o
objects4 = vocab.o rankmodel.o buildrank.o decodemain.o


rankmain : $(objects1)
	g++ $(objects1) -o rankmain

vocab.o : vocab.h

rankmodel.o : rankmodel.h vocab.h gl_defs.h

buildrank.o : buildrank.h rankmodel.h vocab.h gl_defs.h

rankmain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

multimain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

decodemain.o : buildrank.h rankmodel.h vocab.h gl_defs.h


sentence.o : sentence.h gl_defs.h

model12.o : model12.h gl_defs.h vocab.h sentence.h

sortmodel1.o : sortmodel1.h model12.h gl_defs.h vocab.h sentence.h

model1main.o : sortmodel1.h model12.h gl_defs.h vocab.h sentence.h


.PHONY : model1 clean cleanobj multimain decodemain
model1 : $(objects2)
	g++ $(objects2) -o model1

clean :
	rm -rf rankmain model1 multimain decodemain *.o

cleanobj :
	rm -rf *.o

multimain : $(objects3)
	g++ $(objects3) -o multimain

decodemain : $(objects4)
	g++ $(objects4) -o decodemain

