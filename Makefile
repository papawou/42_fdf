NAME := fdf.out

CC := gcc
CFLAGS :=	-Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable -g -fdiagnostics-color=always
endif

INC := -I./inc

SRCDIR := ./src
SRC := main.c draw.c

OBJDIR := ./obj
OBJ := ${addprefix $(OBJDIR)/, ${SRC:.c=.o}}

LIBS := ./libs/libftmlx/libftmlx.a ./libs/libft/libft.a ./libs/mlx/libmlx.a -lXext -lX11 -lm
LIBSINC := -I./libs/libftmlx/inc -I./libs/libft/inc -I./libs/mlx

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

.PHONY : all clean fclean re