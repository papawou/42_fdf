NAME := fdf

CC := gcc
CFLAGS :=	-Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -g -fdiagnostics-color=always
endif

INC := -I./inc

SRCDIR := ./src
SRC := main.c draw.c controls.c cam.c scene.c map.c\
parser/get_next_line/get_next_line_utils.c	parser/get_next_line/get_next_line.c\
parser/parser.c parser/parser_line.c parser/parser_cleaner.c parser/parser_atoi.c

SRC_FTMLX_FILES := img.c img_2.c ftmlx.c \
math/mat.c	math/quat.c math/quat_2.c	math/rot.c	math/trans.c math/trans_2.c	math/vec.c math/vec_2.c \
math/utils.c	math/utils_2.c\
graphics/cam.c \
graphics/print/put_line.c\
color/color.c

SRC_FTMLX := ${addprefix libftmlx/, ${SRC_FTMLX_FILES}}

SRC := $(SRC) $(SRC_FTMLX)

OBJDIR := ./obj
OBJ := ${addprefix $(OBJDIR)/, ${SRC:.c=.o}}

LIBSINC := -I./libs/libft/inc -I./libs/mlx -I/usr/lib
LIBS := ./libs/libft/libft.a ./libs/mlx/libmlx.a

all : $(NAME)

$(NAME)	:	$(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBSINC) $(LIBS) -framework OpenGL -framework AppKit -lm

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