# Executable names:
EXE = pathFinder
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o Airport.o Values.o

# Generated files
CLEAN_RM = Out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk
