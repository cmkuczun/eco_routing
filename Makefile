# This is the Makefile for the Eco Routing (White Boy Sandwich) team project.
# It is based on the provided Makefile for the CSE 20312 course.
#
# Author: Claudia Kuczun
# Date created: April 22, 2022


# COMPILER
PP := g++

# COMPILER FLAGS
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# VARIABLES FOR FOLDERS
INC := include
SRC := src
EXE := exe
OBJ := objects


# COMMAND: make Eco_Routing
Eco_RoutingObjs := $(OBJ)/Eco_Routing.o

Eco_Routing: $(Eco_RoutingObjs)
		$(PP) $(CXXFLAGS) -o $(EXE)/Eco_Routing $(Eco_RoutingObjs)

$(OBJ)/Eco_Routing.o: $(SRC)/Eco_Routing.cpp
		$(PP) $(CXXFLAGS) -c $(SRC)/Eco_Routing.cpp -o $@


# COMMAND: make intialize
initialize:
		mkdir $(OBJ) $(EXE)


# COMMAND: make clean
clean:
		rm -rf $(OBJ)/* $(EXE)/*
