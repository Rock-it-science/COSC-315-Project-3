#COMP = g++
COMP = gcc
#FLAGS = -Wall -g -std=c++0x
FLAGS = -Wall -g

compile:
	$(COMP) $(FLAGS) lab3.create_fs.c -o $@
	$(COMP) $(FLAGS) FileSystem.c -lpthread -o $@


clean:
	rm create
	rm fs