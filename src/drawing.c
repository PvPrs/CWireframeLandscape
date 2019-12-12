/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 09:38:29 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/28 09:38:30 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/includes/libft.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
** @bits_per_pixel will be filled with the
** number of bits needed to represent a pixel color a.k.a depth of the image.
** @size_line
** is the number of bytes used to store one line of the image in memory.
** required to move to a newline in the image.
** Red >> 16, Green >> 8, Blue
*/

static void	illuminate(t_param *ptr, int rgb)
{
	int index;
	int x;
	int y;

	x = ptr->curr.x;
	y = ptr->curr.y;
	if (x > 0 && x < ptr->width && y > 0 && y < ptr->height)
	{
		index = (y * ptr->size_line) + (x * ptr->bits_in_pixel / 8);
		ptr->data_addr[index] = rgb;
		ptr->data_addr[index + 1] = rgb >> 8;
		ptr->data_addr[index + 2] = rgb >> 16;
	}
}

/*
** Rersources for Bresenham Algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
** http://graphics.idav.ucdavis.edu/education \
** /GraphicsNotes/Bresenhams-Algorithm.pdf - good Explanation
** http://members.chello.at/~easyfilter/bresenham.html - sample code
** @param absX
** @param absY
** @param absZ
*/

static void	draw_line_3d(t_param *ptr)
{
	int			error[2];

	ptr->delta_x = abs(ptr->end.x - ptr->start.x);
	ptr->delta_y = abs(ptr->end.y - ptr->start.y);
	error[0] = ptr->delta_x - ptr->delta_y;
	ptr->curr = ptr->start;
	while (ptr->curr.x != ptr->end.x || ptr->curr.y != ptr->end.y)
	{
		illuminate(ptr, get_color(ptr));
		error[1] = error[0] * 2;
		if (error[1] > -ptr->delta_y)
		{
			error[0] -= ptr->delta_y;
			ptr->curr.x += ptr->start.x < ptr->end.x ? 1 : -1;
		}
		if (error[1] < ptr->delta_x)
		{
			error[0] += ptr->delta_x;
			ptr->curr.y += ptr->start.y < ptr->end.y ? 1 : -1;
		}
	}
}

static void	draw_horizontal(t_param *ptr)
{
	int			x;
	int			y;
	t_points	temp;

	x = 0;
	while (x < ptr->map_width)
	{
		ptr->start.y = 0;
		ptr->end.y = 0;
		y = 0;
		while (y < ptr->map_height)
		{
			temp = ptr->end;
			rotate(ptr, ptr->map[y][x]);
			ptr->end.rgb = get_default_color(ptr->map[y][x] * ptr->depth);
			y != 0 ? draw_line_3d(ptr) : 0;
			ptr->start = ptr->end;
			ptr->end = temp;
			ptr->end.y += ptr->tile_size;
			y++;
		}
		ptr->end.x += ptr->tile_size;
		ptr->start.x = ptr->end.x;
		x++;
	}
}

static void	draw_vertical(t_param *ptr)
{
	int			x;
	int			y;
	t_points	temp;

	y = 0;
	while (y < ptr->map_height)
	{
		ptr->start.x = 0;
		ptr->end.x = 0;
		x = 0;
		while (x < ptr->map_width)
		{
			temp = ptr->end;
			rotate(ptr, ptr->map[y][x]);
			ptr->end.rgb = get_default_color(ptr->map[y][x] * ptr->depth);
			x != 0 ? draw_line_3d(ptr) : 0;
			ptr->start = ptr->end;
			ptr->end = temp;
			ptr->end.x += ptr->tile_size;
			x++;
		}
		ptr->end.y += ptr->tile_size;
		ptr->start.y = ptr->end.y;
		y++;
	}
}

/*
** draw_map initializes and sets up the complete drawing of the map.
** @param ptr represents a pointer to the t_param struct.
*/

void		draw_map(t_param *ptr)
{
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->height);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel),
			&(ptr->size_line), &(ptr->endian));
	draw_horizontal(ptr);
	ptr->end.x = 0;
	ptr->end.y = 0;
	draw_vertical(ptr);
	ptr->end.y = 0;
	ptr->end.x = 0;
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	load_interface(ptr);
}
