NAME		= fdf

LIB_PATH	= ./libft/

LIB			= -lmlx -lft -L libft/ -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit

SRC			= src/main.c \
			src/frame.c \
			src/read_map.c \
			src/events/key_events.c \
			src/events/mouse_events.c \
			src/drawing.c
OBJ			= main.o \
			frame.o \
			read_map.o \
			key_events.o \
			mouse_events.o \
			drawing.o

FLAGS		= -Wall -Werror -Wextra

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

all: $(NAME)

$(NAME):
	@make -C $(MINILIBX_DIRECTORY) all
	@make -C $(LIB_PATH) all
	@gcc $(FLAGS) $(SRC) -I $(LIB_PATH) $(LIB) -I $(MINILIBX_HEADERS) -o $(NAME)

clean:
	@make -C $(MINILIBX_DIRECTORY) clean
	@make -C $(LIB_PATH) clean
	@rm -f $(OBJ)

fclean:
	@rm -f $(MINILIBX)
	@make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re:	fclean all