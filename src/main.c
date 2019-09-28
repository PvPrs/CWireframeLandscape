/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/08 12:24:55 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/08 12:24:58 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/fdf.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		**map;
	int index;
	int ind2;
	ind2 = 0;
	index = 0;
	if (argc != 2)
	{
		perror("Usage : ./fdf <filename> [ case_size z_size ]\n");
		strerror(1);
		exit(1);
	}
	map = ft_read_map(argv[1]);
	while (map[index] != NULL)
	{
		while (map[index][ind2] != -1)
		{
			printf("%d ", map[index][ind2++]);
		}
		ind2 = 0;
		index++;
		printf("\n");
	}
	load_frame(750, 750, "FDF Codam project - Dave", map);
	return 0;
}
