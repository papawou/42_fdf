NAME := fdf.out
CC := gcc
CFLAGS :=	-Wall	-Wextra	-Werror

DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS +=	-g -fdiagnostics-color=always
endif

INC := -Iincludes
INC += -Imlx_linux -Lmlx_linux -lmlx -lXext -lX11

SRC_DIR := ./src/
SRC := main.c	mat.c

OBJ_DIR := ./obj/
OBJ := ${SRC:.c=.o}

all : $(NAME)

$(NAME)	:	${addprefix $(OBJ_DIR), $(OBJ)}
	$(CC) $(CFLAGS) $^ $(INC) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< $(INC) -o $@
 
clean :
	$(RM) ${addprefix $(OBJ_DIR), $(OBJ)}

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re