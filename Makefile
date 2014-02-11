objects1 = vocab.o rankmodel.o buildrank.o rankmain.o
objects2 = vocab.o sentence.o model12.o buildmodel12.o trainmodel1main.o
objects3 = vocab.o sentence.o model12.o buildmodel12.o decodemodel1main.o
objects4 = vocab.o rankmodel.o buildrank.o decodemain.o
objects5 = vocab.o rankmodel.o buildrank.o trainmain.o


rankmain : $(objects1)
	g++ $(objects1) -o rankmain

vocab.o : vocab.h

sentence.o : sentence.h gl_defs.h

model12.o : model12.h sentence.h vocab.h gl_defs.h

buildmodel12.o : buildmodel12.h model12.h sentence.h vocab.h gl_defs.h

rankmodel.o : rankmodel.h vocab.h gl_defs.h

buildrank.o : buildrank.h rankmodel.h vocab.h gl_defs.h

decodemain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

trainmain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

decodemodel1main.o : buildmodel12.h model12.h sentence.h vocab.h gl_defs.h

trainmodel1main.o : buildmodel12.h model12.h sentence.h vocab.h gl_defs.h

rankmain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

multimain.o : buildrank.h rankmodel.h vocab.h gl_defs.h

sortmodel1.o : sortmodel1.h model12.h gl_defs.h vocab.h sentence.h

model1main.o : sortmodel1.h model12.h gl_defs.h vocab.h sentence.h


.PHONY : clean cleanobj trainIBM1 decodeIBM1 decodemain trainmain

clean :
	rm -rf rankmain trainIBM1 decodeIBM1 decodemain trainmain *.o

cleanobj :
	rm -rf *.o

trainIBM1 : $(objects2)
	g++ $(objects2) -o trainIBM1

decodeIBM1 : $(objects3)
	g++ $(objects3) -o decodeIBM1

decodemain : $(objects4)
	g++ $(objects4) -o decodemain

trainmain : $(objects5)
	g++ $(objects5) -o trainmain

