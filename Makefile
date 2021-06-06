####################################################
###################### MAKE ########################
####################################################
CONDA_ENV=h
# Need to specify bash in order for conda activate to work.
SHELL=/bin/bash
# Note that the extra activate is needed to ensure that the activate floats env to the front of PATH
CONDA_ACTIVATE=source $$(conda info --base)/etc/profile.d/conda.sh && conda activate && conda activate $(CONDA_ENV)

# EXTENSION= # python3-config --extension-suffix
EXTENSION = .cpython-36m-x86_64-linux-gnu.so
EXECUTAVEL = hbrkga$(EXTENSION)
PATHEXEC = ./bin
PATHSRC= ./src
PATHTEMP = ./.temp
# PYTHON_INCLUDES = # python3 -m pybind11 --includes
PYTHON_INCLUDES = -I/home/mdevino/anaconda3/envs/h/include/python3.6m -I/home/mdevino/anaconda3/envs/h/lib/python3.6/site-packages/pybind11/include

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
CPP = $(CONDA_ACTIVATE) && g++
# Compilation parameters
CCOPT = -std=c++11 -shared -m64 -O3 -g -fPIC $(PYTHON_INCLUDES) -fexceptions -DIL_STD -pthread #-DDEBUG

# Header's include path
CCFLAGS = $(CCOPT)
