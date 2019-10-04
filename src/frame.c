/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/08 11:55:57 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/08 11:55:58 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../includes/fdf.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Almost all the MLX functions return an identifier pointer, which can be later on used for other MLX function calls.
** Note that the MiniLibX can handle an arbitrary number of separate windows.
** @param size_x, size_y
** @param title
** @variable *ptr represents a struct which contains identifiers for MLX to identify with.
*/

void		load_frame(char *title, char *map)
{
	t_param *ptr;

	ptr = (t_param*)malloc(sizeof(t_param));
	init(ptr, map);
	ptr->mlx_ptr = mlx_init();
	if (ptr->mlx_ptr == NULL)
	{
		printf("Failed to initialize connection to the graphical system.\n");
	}
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, ptr->width, ptr->length, title);
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 20, 20, 0xFFFF5C, "mode: ISO");
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	printf("gets here33\n");
	draw_map(ptr);
	printf("gets here34\n");
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	mlx_key_hook(ptr->win_ptr, key_event, ptr);
	mlx_loop(ptr->mlx_ptr);
}

void		init(t_param *ptr, char *map)
{
	ptr->map = ft_read_map(map);
	ptr->zoom = 20;
	printf("gets here 0\n");
	ptr->add = 1;
	ptr->beta = 0;
	ptr->alpha = 0;
	ptr->gamma = 0;
	ptr->width = 1200;
	ptr->length = 750;
	printf("gets here 0\n");
}