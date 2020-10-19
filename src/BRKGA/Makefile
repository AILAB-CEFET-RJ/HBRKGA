# Macros:
CPP= g++
CFLAGS= -O3 -fopenmp
#OBJECTS= SampleDecoder.o samplecode.o

all: code

code: main.o SampleDecoder.o AG.h BRKGA.h
	$(CPP) $(CFLAGS) -o code main.o SampleDecoder.o
        
main.o: main.cpp AG.h BRKGA.h
	$(CPP) $(CFLAGS) -c main.cpp

SampleDecoder.o: SampleDecoder.cpp BRKGA.h
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp

# Remove:
clean:
	rm -f *.o code 
