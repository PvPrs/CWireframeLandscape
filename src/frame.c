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
		printf("Failed to initialize connection to the graphical system.\n");
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, ptr->width, ptr->length, title);
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	mlx_hook(ptr->win_ptr, 2, 0, key_event, ptr); // Key Presses
	mlx_hook(ptr->win_ptr, 4, 0, mouse_event, ptr); // Mouse Presses
	mlx_hook(ptr->win_ptr, 17, 0, close_frame, ptr); // Red Close Button
	mlx_hook(ptr->win_ptr, 6, 0, mouse_move, ptr); // Mouse Movement
	draw_map(ptr);
	mlx_loop(ptr->mlx_ptr);
}
/**
 * Load any additional interfaces
 * @param ptr
 */
void		load_interface(t_param *ptr)
{
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 20, 20, 0xFFFF5C, ptr->fov == PARALLEL ? "mode: PARALLEL" : "mode: ISOMETRIC");
}

int		close_frame(void *ptr)
{
	//todo: Shutdown confirmation window.
	(void)ptr;
	exit(0);
}

/**
 * Initialize all the required variables.
 * @param ptr
 * @param map
 */
void		init(t_param *ptr, char *map)
{
	ptr->width = 1200;
	ptr->length = 750;
	ptr->zoom = 20;
	ptr->depth = 1;
	ptr->beta = 0;
	ptr->alpha = 0;
	ptr->gamma = 0;
	ptr->map_width = 0;
	ptr->map_height = 0;
	ptr->start.x = 0;
	ptr->start.y = 0;
	ptr->start.z = 0;
	ptr->end.x = 0;
	ptr->end.y = 0;
	ptr->end.z = 0;
	ptr->fov = PARALLEL;
	ptr->map = ft_read_map(map, ptr);
}