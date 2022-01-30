NAME := a.out

CC := gcc
CFLAGS :=	-Wall	-Wextra	-Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS +=	-g -fdiagnostics-color=always
endif

INC := -I./inc
LIBS := 

SRC_DIR := ./src
SRC := 

OBJ_DIR := ./obj
OBJ := ${addprefix $(OBJ_DIR)/, ${SRC:.c=.o}}

all : $(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(LIBS)

clean :
	${RM} $(OBJ)

fclean : clean
	${RM} $(NAME)

re : fclean all

.PHONY : all clean fclean re