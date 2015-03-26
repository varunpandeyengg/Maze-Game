#***********************************************************************************
# * Design & Analysis of Algorithm - Project
# * File name 	: Makefile
# * Module 	: Maze.out
# * Description	: Make infrastructure for the project.
#***********************************************************************************

CC=g++
CC_FLAGS=-lglut -lGL #-lgraph

all: maze.cpp cell.cpp grid.cpp
	$(CC) $(CC_FLAGS) cell.cpp grid.cpp maze.cpp -o Maze

debug: CC_FLAGS+=-g
debug: all
	
clean:
	rm -rvf Maze core* *.o a.out 

