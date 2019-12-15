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

static void		free_lines(t_lines *lst, int size)
{
	t_lines *temp;
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
	t_lines *head;

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

	lst = malloc(sizeof(*lst));
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
	lst = NULL;
	ptr->map_width = ft_2d_len(ft_strsplit(head->str, ' '));
	return (sort_map(head, ptr));
}
