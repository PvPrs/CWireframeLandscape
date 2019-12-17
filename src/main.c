/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/08 12:24:55 by dvan-boc       #+#    #+#                */
/*   Updated: 2019/12/17 18:09:28 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc != 2 || ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".fdf") != 0)
	{
		perror("Usage : ./fdf <filename> [ case_size z_size ]\n");
		strerror(1);
		exit(1);
	}
	load_frame("FDF Codam project - Dave & Brendan", argv[1]);
	return (0);
}
