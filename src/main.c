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
#include "../includes/fdf.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Usage : ./fdf <filename> [ case_size z_size ]\n");
		strerror(1);
		exit(1);
	}
	load_frame("FDF Codam project - Dave & Brendan", argv[1]);
	while (1)
	{
		if (getchar())
			break;
	}
	return (0);
}

/*
** @TODO: Make a shutdown window, free all the memory
*/