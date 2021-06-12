CC = g++ 
CCFLAGS1 = -g 
CCFLAGS2 = -lncurses
CCFLAGS3 = -pthread

all: main

main: Snake.o Item.o Gate.o main.o map.h LOC.h Item.h GrowthItem.h PoisonItem.h Gate.h main.cpp Snake.cpp Item.cpp Gate.cpp
	$(CC) $(CCFLAGS1) -o $@ main.o Snake.o Item.o Gate.o $(CCFLAGS2) $(CCFLAGS3)
	
clean:
	rm -rf *.o

# Item.o: Item.cpp Item.h
# 	$(CC) $(CCFLAGS1) -c $< -pthread
	
%.o : %.cpp %.h
	$(CC) $(CCFLAGS1) -c $< $(CCFLAGS2) $(CCFLAGS3)

%.o : %.cpp
	$(CC) $(CCFLAGS1) -c $< $(CCFLAGS2) $(CCFLAGS3)

% : %.cpp
	$(CC) $(CCFLAGS1) -o $@ $< $(CCFLAGS2) $(CCFLAGS3)
