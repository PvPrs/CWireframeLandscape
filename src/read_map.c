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
 *
 * @param file
 * @return
 * @map ** represents the X-axis(horizontal), * represents the Y-Axis(vertical)
 */
int			**ft_read_map(char *file)
{
	int count;
	int fd;
	char *line;
	t_lines *lst;
	t_lines *head;

	count = 0;
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
		count++;
		lst->next = malloc(sizeof(*lst));
		lst = lst->next;
	}
	return (sort_map(head, count, (ft_strlen(head->str) / 3) + 1));
}

int		**sort_map(t_lines *lst, int size, int len)
{
	int		index;
	int		row;
	char	**split_line;
	int		**map;

	map = malloc(sizeof(int *) * size + 1);
	map[size] = NULL;
	row = 0;
	index = 0;
	while (row < size)
	{
		split_line = ft_strsplit(lst->str, ' ');
		while (split_line[index] != NULL)
			printf("row: %d %s\n", row, split_line[index++]);
		map[row] = malloc(sizeof(int) * len + 1);
		while (index < len)
		{
			//printf("%d\n", ft_atoi(split_line[index]));
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