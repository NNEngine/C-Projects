# This define a make variable called CC ansd assigns it to value GCC which is the GNU Compiler Collection for C
# It's a convention to name the C compilier variable as CC. This allows easy subtitution if you want to use a different compiler later (e.g. clang)
CC = gcc

# This defines another make variable CFLAGS which contains the compiler flags
# -Wall: Enables all the common warning messages
# - Wextra: Enables additonal warnings not covered by -Wall
# These flags help catch potential bugs and enforce cleaner code by showing compiler warnings
CFLAGS = -Wall -Wextra

DEPS = utils.h lib.h dirent.h

# Define a list of object file needed to build the final program
# main.o is compiled from main.c and utils.o from utils.c
# Used to specify the components of the final executable
OBJS = main.o utils.o

# This defines a target named all, which is usually the default target when you run make
# It depends on the explorer target, so running make will build explorer
all: explorer

# This target builds the final executable names explorer.
# It depends on the object files main.o and utils.o (from ${OBJS})
# If either .0 file is missing or older than its .c file, they will be rebuilt

# This i the recipe (command) for building the explorer executable
# It runs gg -o explorer main.o utils.o
# -o explorer: specifies the output file name
# ${OBJS}: the object files to link 
explorer: ${OBJS}
	${CC} -o explorer ${OBJS}


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# This deines a target named clean
# It is not a file, just a utility rule for cleanup

# This is the command run when 'make clean' is executed
# rm -f *.o explorer: forcefully delets all the object files (*.o) and executable explorer
# -f suppresses errors if files don't exist
clean:
	rm -f *.o explorer


# *-----------------------------------------------------------------------------*
# 'make' sees the default target is all, which depends on explorer
# To build explorer, it needs main.o and utils.o
# If these don't exist, it will try to compile main.c -> main.o and utils.c -> utils.o using implicit rules (like gcc -c main.c -o main.o)
# Once the object files are present, it runs: gcc -o explorer main.o utils.o, This produces the explorer main.o utils.o
# In windows, if you are using MinGW or WSL, these executable may be named explorer.exe, you can run it with ./explorer