##
## titanfrigel
## my_malloc
## File description:
## Makefile
##

CC = gcc

CFLAGS = -W -Wall -Wextra -g2 -O2

INCLUDES = -I./include

LFLAGS =

LIBS =

SRC_PATH = src/

SRCS_NAME = my_malloc.c

LIBNAME = libmy_malloc.so

SRCS = $(patsubst %, $(SRC_PATH)%, $(SRCS_NAME))

OBJS = $(SRCS:.c=.o)

all : $(LIBNAME)

$(LIBNAME) : $(OBJS)
	$(CC) -shared $(CFLAGS) $(INCLUDES) -o $(LIBNAME) $(OBJS) $(LFLAGS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	$(RM) $(OBJS) *~

fclean : clean
	$(RM) $(LIBNAME)

re : fclean all
