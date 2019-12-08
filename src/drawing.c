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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define X 1
#define Y 0

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
		ptr->data_addr[index + 3] = 0;
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
	double lead_axis;
	double index;
	double x_incr;
	double y_incr;

	index = 0;
	ptr->delta_x = ptr->end.x - ptr->start.x;
	ptr->delta_y = ptr->end.y - ptr->start.y;
	ptr->curr = ptr->start;
	lead_axis = fabs(ptr->delta_x) > fabs(ptr->delta_y) ?
				fabs(ptr->delta_x) : fabs(ptr->delta_y);
	x_incr = ptr->delta_x / lead_axis;
	y_incr = ptr->delta_y / lead_axis;
	while (index < lead_axis)
	{
		illuminate(ptr, ptr->end.z != 0 ? get_color(ptr) : ptr->start_rgb);
		ptr->curr.x += x_incr;
		ptr->curr.y += y_incr;
		index++;
	}
}

static void	draw_horizontal(t_param *ptr)
{
	int			x;
	int			y;
	t_points	temp;

	x = 0;
	ptr->end.x = 0;
	while (x < ptr->map_width)
	{
		ptr->start.y = 0;
		ptr->end.y = 0;
		y = 0;
		while (y < ptr->map_height)
		{
			temp = ptr->end;
			rotate(ptr, ptr->map[y][x]);
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
	ptr->end.y = 0;
	while (y < ptr->map_height)
	{
		ptr->start.x = 0;
		ptr->end.x = 0;
		x = 0;
		while (x < ptr->map_width)
		{
			temp = ptr->end;
			rotate(ptr, ptr->map[y][x]);
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
** draw_map initializes andd sets up the complete drawing of the map.
** @param ptr represents a pointer to the t_param struct.
*/

void		draw_map(t_param *ptr)
{
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->height);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel),
			&(ptr->size_line), &(ptr->endian));
	draw_horizontal(ptr);
	ptr->end.x = 0;
	draw_vertical(ptr);
	ptr->end.y = 0;
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	load_interface(ptr);
}
