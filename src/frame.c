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

void		load_frame(int size_x, int size_y, char *title, int **map)
{
	t_param *ptr;
	int		row;
	int		col;

	row = 0;
	col = 0;
	ptr = (t_param*)malloc(sizeof(t_param));
	ptr->mlx_ptr = mlx_init();
	if (ptr->mlx_ptr == NULL)
	{
		printf("Failed to initialize connection to the graphical system.\n");
	}
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, size_x, size_y, title);
	mlx_string_put(ptr->mlx_ptr, ptr->win_ptr, 20, 20, 0xFFFF5C, "mode: ISO");
	ptr->img = mlx_new_image(ptr->mlx_ptr, 19, 11);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &ptr->bits_in_pixel, &ptr->size_line, &ptr->endian);
	draw_line_3d(0, 18, 0, 10, ptr->img);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	while (map[row] != NULL)
		row++;
	mlx_key_hook(ptr->win_ptr, key_event, ptr);

	mlx_loop(ptr->mlx_ptr);
}

void		load_pop_up(int size_x, int size_y, char *title)
{

}