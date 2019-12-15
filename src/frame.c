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
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Almost all the MLX functions return an identifier pointer
** which can be later on used for other MLX function calls.
** Note that the MiniLibX can handle an arbitrary n of separate windows.
** @param size_x, size_y
** @param title
** @variable *ptr represents a struct of identifiers for MLX to identify with.
*/

void	load_frame(char *title, char *map)
{
	struct s_param ptr;

	ft_bzero(&ptr, sizeof(struct s_param));
	ptr.map = ft_read_map(map, &ptr);
	init(&ptr);
	ptr.mlx_ptr = mlx_init();
	if (ptr.mlx_ptr == NULL)
	{
		printf("Failed to initialize connection to the graphical system.\n");
		exit(1);
	}
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.width, ptr.height, title);
	mlx_hook(ptr.win_ptr, 2, 0, key_event, &ptr);
	mlx_hook(ptr.win_ptr, 4, 0, mouse_event, &ptr);
	mlx_hook(ptr.win_ptr, 17, 0, close_frame, &ptr);
	draw_map(&ptr);
	mlx_loop(ptr.mlx_ptr);
}

/*
** Load any additional interfaces
** @param ptr
*/

void	load_interface(struct s_param *ptr)
{
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 20, 20, 0xFFFFFF,
			"Reset to default.");
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 20, 37, 0xFFFFFF, "View:");
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 73, 37, 0xFF0000,
			ptr->fov == PARALLEL ? "parallel" : "isometric");
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 73, 37, 0xFF0000,
			ptr->fov == PARALLEL ? "parallel" : "isometric");
}

int		close_frame(struct s_param *ptr)
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

/*
** Initialize all the required variables.
** @param ptr
** @param map
*/

void	init(struct s_param *ptr)
{
	ptr->endian = 0;
	ptr->width = 1200;
	ptr->height = 750;
	ptr->tile_size = 40;
	ptr->depth = 2;
	ptr->beta = 0;
	ptr->alpha = 0;
	ptr->gamma = 0;
	ptr->start.x = 0;
	ptr->start.y = 0;
	ptr->start.z = 0;
	ptr->end.x = 0;
	ptr->end.y = 0;
	ptr->end.z = 0;
	ptr->fov = PARALLEL;
}
