NAME := fdf.out

CC := gcc
CFLAGS :=	-Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -g -fdiagnostics-color=always
endif

INC := -I./inc

SRCDIR := ./src
SRC := main.c

OBJDIR := ./obj
OBJ := ${addprefix $(OBJDIR)/, ${SRC:.c=.o}}

LIBS := ./libs/libft/libft.a ./libs/libftmlx/libftmlx.a -lm
LIBSINC := -I./libs/libft/inc -I./libs/libftmlx/inc

all : $(NAME)

$(NAME)	:	$(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBSINC) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(LIBSINC)

%.a :
	make -C $(@D)

clean :
	${RM} $(OBJ)

fclean : clean
	${RM} $(NAME)

re : fclean all

.PHONY : all clean fclean re $(LIBS)