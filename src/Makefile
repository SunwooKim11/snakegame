CC = g++ 
CCFLAGS1 = -g 
CCFLAGS2 = -lncurses
CCFLAGS3 = -pthread

all: main

main: main.o Snake.o map.h LOC.h main.cpp Snake.cpp
	$(CC) $(CCFLAGS1) -o $@ main.o Snake.o $(CCFLAGS2) 
	
clean:
	rm -rf *.o

%.o : %.cpp %.h
	$(CC) $(CCFLAGS1) -c $< $(CCFLAGS2)

%.o : %.cpp
	$(CC) $(CCFLAGS1) -c $< $(CCFLAGS2)

% : %.cpp
	$(CC) $(CCFLAGS1) -o $@ $<