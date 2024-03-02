#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#CC specifies which compiler we're using
CC = clang++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -Wextra -Wpedantic -Werror

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -I inc -Wl,-rpath lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -L lib
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = qlearning

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
