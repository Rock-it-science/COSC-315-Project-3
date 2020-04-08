#COMP = g++
COMP = gcc
#FLAGS = -Wall -g -std=c++0x
FLAGS = -Wall -g

all: lab3

mini_project: FileSystem.c
	$(COMP) $(FLAGS) FileSystem.c -lpthread -o $@

clean:
	rm -f mini_project*.o