# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/17 16:46:40 by bprado         #+#    #+#                 #
#    Updated: 2019/12/17 20:46:31 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME				= fdf

LIB_PATH			= ./libft/

FRAMEWORK			= -framework OpenGL -framework AppKit

DEPENDENCIES		= -lmlx -lft -L $(LIB_PATH) -L $(MINILIBX_DIRECTORY) \
					$(FRAMEWORK) $(INC)

SRC					= $(wildcard src/*.c)

INC					= -I includes -I libft/includes

OBJ					= $(patsubst src/%.c,obj/%.o,$(SRC))

CFLAGS				= -Wall -Werror -Wextra

MINILIBX 			= $(MINILIBX_DIRECTORY)/libmlx.a

MINILIBX_DIRECTORY 	= ./minilibx_macos


all: $(NAME)

$(NAME): minilibx_macos/libmlx.a libft/libft.a $(OBJ) 
	@echo "something magical is about to happen..."
	@$(CC) $(OBJ) $(DEPENDENCIES) -o $(NAME)

obj/%.o: src/%.c includes/fdf.h
	@echo "working on object files..."
	@mkdir -p obj
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

minilibx_macos/libmlx.a: FORCE
	@echo "minilibx stuff..."
	@$(MAKE) CFLAGS=-Wno-deprecated-declarations -C $(MINILIBX_DIRECTORY)

libft/libft.a: FORCE
	@echo "Homemade libft..."
	@$(MAKE) -C $(LIB_PATH)

clean:
	@echo "lets clean..."
	@$(MAKE) clean -C $(MINILIBX_DIRECTORY)
	@$(MAKE) clean -C $(LIB_PATH)
	@rm -rf obj

fclean:	clean
	@rm -f $(MINILIBX)
	@$(MAKE) fclean -C $(LIB_PATH)
	@rm -f $(NAME)

re:	fclean all

FORCE:

.PHONY: all clean fclean re FORCE
