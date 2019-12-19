# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dvan-boc <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/24 14:00:38 by dvan-boc       #+#    #+#                 #
#    Updated: 2019/12/17 20:44:02 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

HEADER 		= includes/

SRC			= \
			fd/ft_putchar_fd.c \
			fd/ft_putendl_fd.c \
			fd/ft_putnbr_fd.c \
			fd/ft_putstr_fd.c \
			io/get_next_line.c \
			list/ft_lstadd.c \
			list/ft_lstdel.c \
			list/ft_lstdelone.c \
			list/ft_lstiter.c \
			list/ft_lstmap.c \
			list/ft_lstnew.c \
			mem/ft_2d_len.c \
			mem/ft_free_array.c \
			mem/ft_memalloc.c \
			mem/ft_memccpy.c \
			mem/ft_memchr.c \
			mem/ft_memcmp.c \
			mem/ft_memcpy.c \
			mem/ft_memdel.c \
			mem/ft_memmove.c \
			mem/ft_memset.c \
			print/ft_putchar.c \
			print/ft_putendl.c \
			print/ft_putnbr.c \
			print/ft_putstr.c \
			string/ft_bzero.c \
			string/ft_char_occur.c \
			string/ft_revstr.c \
			string/ft_strcat.c \
			string/ft_strchr.c \
			string/ft_strclr.c \
			string/ft_strcmp.c \
			string/ft_strcpy.c \
			string/ft_strdel.c \
			string/ft_strdup.c \
			string/ft_strequ.c \
			string/ft_striter.c \
			string/ft_striteri.c \
			string/ft_strjoin.c \
			string/ft_strlcat.c \
			string/ft_strlen.c \
			string/ft_strmap.c \
			string/ft_strmapi.c \
			string/ft_strncat.c \
			string/ft_strncmp.c \
			string/ft_strncpy.c \
			string/ft_strnequ.c \
			string/ft_strnew.c \
			string/ft_strnstr.c \
			string/ft_strrchr.c \
			string/ft_strsplit.c \
			string/ft_strstr.c \
			string/ft_strsub.c \
			string/ft_strtolower.c \
			string/ft_strtoupper.c \
			string/ft_strtrim.c \
			utils/ft_atoi.c \
			utils/ft_bit_to_max_int.c \
			utils/ft_isalnum.c \
			utils/ft_isalpha.c \
			utils/ft_isascii.c \
			utils/ft_isdigit.c \
			utils/ft_isprime.c \
			utils/ft_isprint.c \
			utils/ft_itoa.c \
			utils/ft_reinitialize.c \
			utils/ft_sqrt.c \
			utils/ft_tolower.c \
			utils/ft_toupper.c \

OBJ			= $(patsubst %.c,bin/%.o,$(SRC))

CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bin/%.o: src/%.c includes/libft.h includes/get_next_line.h
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFALGS) -I $(HEADER)

clean:
	rm -rf bin

fclean: clean
	rm -rf $(NAME)

re: fclean all
