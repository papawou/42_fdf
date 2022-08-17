NAME := fdf.out

CC := gcc
CFLAGS :=	-Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -g -fdiagnostics-color=always
endif

INC := -I./inc

SRCDIR := ./src
SRC := main.c draw.c controls.c shader_map_mesh.c parser.c parser_2.c cleaner.c scene.c\
libs/get_next_line/get_next_line_utils.c	libs/get_next_line/get_next_line.c

OBJDIR := ./obj
OBJ := ${addprefix $(OBJDIR)/, ${SRC:.c=.o}}

LIBS := ./libs/libftmlx/libftmlx.a ./libs/libft/libft.a ./libs/mlx/libmlx.a -lXext -lX11 -lm
LIBSINC := -I./libs/libftmlx/inc -I./libs/libft/inc -I./libs/mlx -I/usr/lib

all : $(NAME)

#-framework OpenGL -framework AppKit
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