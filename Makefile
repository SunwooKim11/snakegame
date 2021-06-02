CC = g++ 
CCFLAGS1 = -g 
CCFLAGS2 = -lncurses
CCFLAGS3 = -pthread

all: main

main: main.o Snake.o map.h LOC.h
	$(CC) $(CCFLAGS1) $@ $^ $(CCFLAGS2) 
clean:
	rm -rf *.o

%.o : %.cpp %.h
	$(CC) $(CCFLAGS1) -c $< $(CCFLAGS2)

# %.o : %.cpp
# 	$(CC) $(CCFLAGS1) -c $<

# % : %.cpp
# 	$(CC) $(CCFLAGS1) -o $@ $<