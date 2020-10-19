####################################################
###################### MAKE ########################
####################################################

EXECUTAVEL = hypAG
PATHEXEC = ./bin
PATHSRC= ./src
PATHTEMP = ./.temp

all:
	mkdir -p $(PATHEXEC)
	mkdir -p $(PATHTEMP)
	make $(EXECUTAVEL)

#Juntando todos os objetos e gerando o programa
$(EXECUTAVEL): $(PATHTEMP)/path_relinking.o $(PATHTEMP)/random_walk.o $(PATHTEMP)/ES.o $(PATHTEMP)/SampleDecoder.o  $(PATHTEMP)/FWChrono.o $(PATHTEMP)/solution.o  $(PATHTEMP)/main.o
	$(CPP) $(CCFLAGS) $(PATHTEMP)/path_relinking.o $(PATHTEMP)/random_walk.o $(PATHTEMP)/ES.o $(PATHTEMP)/SampleDecoder.o $(PATHTEMP)/FWChrono.o $(PATHTEMP)/solution.o $(PATHTEMP)/main.o -o $(PATHEXEC)/$(EXECUTAVEL)

$(PATHTEMP)/main.o: $(PATHSRC)/main.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/main.cpp -o $(PATHTEMP)/main.o

$(PATHTEMP)/solution.o: $(PATHSRC)/solution.cpp
	$(CPP) -std=c++11 $(CCFLAGS) -c $(PATHSRC)/solution.cpp -o $(PATHTEMP)/solution.o

$(PATHTEMP)/FWChrono.o: $(PATHSRC)/FWChrono.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/FWChrono.cpp -o $(PATHTEMP)/FWChrono.o

$(PATHTEMP)/SampleDecoder.o: $(PATHSRC)/BRKGA/SampleDecoder.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/BRKGA/SampleDecoder.cpp -o $(PATHTEMP)/SampleDecoder.o

$(PATHTEMP)/ES.o: $(PATHSRC)/ES.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/ES.cpp -o $(PATHTEMP)/ES.o

$(PATHTEMP)/random_walk.o: $(PATHSRC)/random_walk.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/random_walk.cpp -o $(PATHTEMP)/random_walk.o

$(PATHTEMP)/path_relinking.o: $(PATHSRC)/path_relinking.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/path_relinking.cpp -o $(PATHTEMP)/path_relinking.o
####################################################
###################### CLEAN #######################
####################################################
clean:
	rm -rf $(PATHEXEC)
	rm -rf $(PATHTEMP)

####################################################
##################### COMPILER #####################
####################################################

##### COMPILER CONFIGURATION's
# Compiler
CPP = g++
# Compilation parameters
CCOPT = -std=c++11 -m64 -O3 -g -fPIC -fexceptions -DIL_STD -pthread #-DDEBUG

# Header's include path
CCFLAGS = $(CCOPT)
