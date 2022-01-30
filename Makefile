NAME := a.out

CC := gcc
CFLAGS :=	-Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS +=	-g -fdiagnostics-color=always
endif

INC := -I./inc
LIBSINC := -I./libs/libft -I./libs/libftmlx/inc
LIBS := ./libs/libft/libft.a ./libs/libftmlx/libftmlx.a

SRC_DIR := ./src
SRC := main.c

OBJ_DIR := ./obj
OBJ := ${addprefix $(OBJ_DIR)/, ${SRC:.c=.o}}

all : $(NAME) 

$(NAME)	:	$(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBSINC) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(LIBSINC)

%.a :
	make -C $(@D)

clean :
	${RM} $(OBJ)

fclean : clean
	${RM} $(NAME)

re : fclean all

.PHONY : all clean fclean re