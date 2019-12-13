/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 16:11:27 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/06/13 16:11:31 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_free_array(void **arr)
{
	char **temp;
	int index;

	index = 0;
	temp = arr;
	while (temp[index] != NULL)
	{
		free(temp[index]);
		index++;
	}
	free(temp[index]);
	free(temp);
	temp = NULL;
}



int		close_frame(t_param *ptr)
{
	int **map;
	int index;

	index = 0;
	map = ptr->map;
	while (map[index] != NULL)
	{
		free(map[index]);
		++index;
	}
	free(map[index]);
	free(map);
	exit(0);
}
