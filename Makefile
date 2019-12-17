# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/17 16:46:40 by bprado         #+#    #+#                 #
#    Updated: 2019/12/17 19:24:51 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME				= fdf

LIB_PATH			= ./libft/

FRAMEWORK			= -framework OpenGL -framework AppKit

DEPENDENCIES		= -lmlx -L $(LIB_PATH) -lft -L $(MINILIBX_DIRECTORY) $(FRAMEWORK) $(INC)

SRC					= $(wildcard src/*.c)

INC					= -I includes -I libft/includes

OBJ					= $(patsubst src/%.c,obj/%.o,$(SRC))

FLAGS				= -Wall -Werror -Wextra

MINILIBX 			= $(MINILIBX_DIRECTORY)/libmlx.a

MINILIBX_DIRECTORY 	= ./minilibx_macos


all: $(NAME)

$(NAME): $(OBJ) libft/libft.a minilibx_macos/libmlx.a
	@echo "something magical is about to happen..."
	@gcc $(FLAGS) $(SRC) $(DEPENDENCIES) -o $(NAME)

obj/%.o: src/%.c includes/fdf.h
	@mkdir -p obj
	$(CC) -c $(FLAGS) $(INC) -o $@ $<

minilibx_macos/libmlx.a: $(wildcard minilibx_macos/*.c)
	@$(MAKE) -C $(MINILIBX_DIRECTORY)

libft/libft.a: $(wildcard libft/*.c)
	@$(MAKE) -C $(LIB_PATH)

clean:
	@echo "lets clean..."
	@make clean -C $(MINILIBX_DIRECTORY)
	@make clean -C $(LIB_PATH)
	@rm -rf obj

fclean:	clean
	@rm -f $(MINILIBX)
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)

re:	fclean all