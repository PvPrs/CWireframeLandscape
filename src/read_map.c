/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/07 15:13:27 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/07 15:13:28 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "../minilibx_macos/mlx.h"
#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

/**
 * Frees all the allocated nodes of s_lines
 * @param lst
 * @param size
 */
static void		free_lines(struct s_lines *lst, int size)
{
	struct s_lines *temp;
	int index;

	index = 0;
	while (index < size)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
		index++;
	}
	free(lst);
}

/*
** Sorts the input into a 2D Pointer Array delimited by spaces.
** @param lst represents a linked-list cointaining a single line.
** @return A Pointer-to-Pointer Int Array
*/

static int	**sort_map(struct s_lines *lst, struct s_param *ptr)
{
	int		index;
	int		row;
	char	**split_line;
	int		**map;
	struct s_lines *head;

	head = lst;
	map = malloc(sizeof(*map) * (ptr->map_height + 1));
	map[ptr->map_height] = NULL;
	row = 0;
	index = 0;
	while (row < ptr->map_height && lst->next != NULL)
	{
		split_line = ft_strsplit(lst->str, ' ');
		map[row] = malloc(sizeof(**map) * (ptr->map_width + 1));
		while (index < ptr->map_width)
		{
			map[row][index] = ft_atoi(split_line[index]);
			index++;
		}
		map[row][index] = -1;
		index = 0;
		row++;
		lst = lst->next;
		ft_free_array(split_line);
	}
	free_lines(head, row);
	return (map);
}

/*
** @param file represents the file name.
** @return sort_map returns an 2D int array.
** Stores every line into a linked list, to get sorted by sort_map.
*/

int			**ft_read_map(char *file, struct s_param *ptr)
{
	int				fd;
	char			*line;
	struct s_lines	*lst;
	struct s_lines	*head;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("File not found.\n");
		exit(1);
	}
	lst = malloc(sizeof(*lst));
	head = lst;
	while (get_next_line(fd, &line))
	{
		lst->str = line;
		ptr->map_height++;
		lst->next = malloc(sizeof(*lst));
		lst = lst->next;
	}
	lst = NULL;
	ptr->map_width = ft_2d_len(ft_strsplit(head->str, ' '));
	return (sort_map(head, ptr));
}
