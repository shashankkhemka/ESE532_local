# Makefile from https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -O2 -Wno-unused-label

# define any directories containing header files other than /usr/include
# e.g. -I/home/newhall/include  -I../include
INCLUDES = -I/src/sw/ -I/src/host/

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like: -L/home/newhall/lib  -L../lib
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
#   -L/home/newhall/lib  -L../lib
LIBS =

# define the C source files
SRCS = ./src/host/3d_rendering_host.cpp ./src/host/utils.cpp ./src/host/check_result.cpp ./src/sw/rendering_sw.cpp

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file
MAIN = rendering
GPROF_MAIN = rendering_instrumented

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean profile

all:    $(MAIN)
	@echo  Executable $(MAIN) compiled!

gprof:	$(GPROF_MAIN)
	@echo  Executable $(GPROF_MAIN) compiled!
	@echo  Running ./$(GPROF_MAIN) to get gmon.out for gprof...
	@./$(GPROF_MAIN)
	@echo  Running gprof -p ./$(GPROF_MAIN)...
	@gprof -p ./$(GPROF_MAIN)

perf: all
	@echo Running perf stat...
	@sudo perf stat ./$(MAIN)

$(MAIN): $(OBJS)
	$(CC) -DWITH_TIMER $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(GPROF_MAIN): $(OBJS)
	$(CC) -pg $(CFLAGS) $(INCLUDES) -o $(GPROF_MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) -rf perf* Output.bin *.txt *.out *.o *~ $(MAIN) $(GPROF_MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
