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

/*
** Sorts the read integers into a 2D Pointer Array
** @param lst represents a linked-list cointaining the strings
** @param size represents the amount of rows
** @param len represents the width of the rows
** @return A Pointer-to-Pointer Int Array
*/

static int	**sort_map(t_lines *lst, t_param *ptr)
{
	int		index;
	int		row;
	char	**split_line;
	int		**map;

	map = malloc(sizeof(int *) * (ptr->map_height + 1));
	map[ptr->map_height] = NULL;
	row = 0;
	index = 0;
	while (row < ptr->map_height)
	{
		split_line = ft_strsplit(lst->str, ' ');
		map[row] = malloc(sizeof(int) * (ptr->map_width + 1));
		while (index < ptr->map_width)
		{
			map[row][index] = ft_atoi(split_line[index]);
			index++;
		}
		map[row][index] = -1;
		index = 0;
		row++;
		lst = lst->next;
	}
	return (map);
}

/*
** @param file
** @return
** @map ** represents the X-axis(horizontal), * represents the Y-Axis(vertical)
*/

int			**ft_read_map(char *file, t_param *ptr)
{
	int		fd;
	char	*line;
	t_lines	*lst;
	t_lines	*head;

	lst = malloc(sizeof(t_lines *));
	head = lst;
	if (!(ft_strcmp(ft_strrchr(file, '.'), ".fdf") == 0))
	{
		ft_putstr("No Data found.\n");
		exit(1);
	}
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		lst->str = line;
		ptr->map_height++;
		lst->next = malloc(sizeof(*lst));
		lst = lst->next;
	}
	ptr->map_width = ft_strlen(head->str) / 3 + 1;
	return (sort_map(head, ptr));
}
