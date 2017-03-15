ELF = bin/main.elf


INC = -I.


CC = g++
LD = g++
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size

CFLAGS = -O2 -Os -s -Wall -Wextra -pedantic -std=c++11 $(INC)
LDFLAGS = -lm -lpthread -pthread -std=c++11 -lglut -lGL -lGLU


SRCS = $(shell find -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)



all: $(ELF)
	$(SIZE) $(ELF)

$(ELF): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJS) -rf
