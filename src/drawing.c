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

/**
 * @TODO: X should move across the columns (left to right), and Y should move down the rows (top to bottom).
 */

#define X 1
#define Y 0

/**
* @bits_per_pixel will be filled with the
* number of bits needed to represent a pixel color (also called the depth of the image).
* @size_line is the number of bytes used to store one line
* of  the  image  in memory.  This information is needed to move from one
* line to another in the image.
*/
static void		illuminate(t_param *ptr, int rgb)
{
	int index;
	int xAxis;
	int yAxis;

	xAxis = ptr->curr.x;
	yAxis = ptr->curr.y;
//	printf("%f + %f, size_line: %d, bits: %d\n", xAxis, yAxis, ptr->size_line, ptr->bits_in_pixel / 8);
//	printf("red: %d, green: %d, blue %d\n", rgb >> 16, rgb >> 8, rgb);
	if (xAxis >= 0 && xAxis <= ptr->width && yAxis >= 0 && yAxis <= ptr->height)
	{
		index = (yAxis * ptr->size_line) + (xAxis * ptr->bits_in_pixel / 8);
		ptr->data_addr[index] = rgb; // B — Blue
		ptr->data_addr[index + 1] = rgb >> 8; // G — Green
		ptr->data_addr[index + 2] = rgb >> 16; // R — Red
		ptr->data_addr[index + 3] = 0; // Alpha channel
	}
}

/*
** Rersources for Bresenham Algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
** http://graphics.idav.ucdavis.edu/education/GraphicsNotes/Bresenhams-Algorithm.pdf - good Explanation
** http://members.chello.at/~easyfilter/bresenham.html - sample code
** @param absX
** @param absY
** @param absZ
** @TODO: This bresenham algo needs fixing and is the cause of the incorrect drawing.
*/
static void		draw_line_3d(t_param *ptr, int color)
{
	double leadAxis;
	double xincrement;
	double index;
	double yincrement;

	index = 0;
	ptr->delta_x = ptr->end.x - ptr->start.x;
	ptr->delta_y = ptr->end.y - ptr->start.y;
	ptr->curr.x = ptr->start.x;
	ptr->curr.y = ptr->start.y;
	leadAxis = fabs(ptr->delta_x) > fabs(ptr->delta_y) ? fabs(ptr->delta_x) : fabs(ptr->delta_y);
	xincrement = ptr->delta_x / (float) leadAxis;
	yincrement = ptr->delta_y / (float) leadAxis;
	while (index < leadAxis)
	{
		ptr->curr.x += xincrement;
		ptr->curr.y += yincrement;
		if (ptr->curr.x > 0 && ptr->curr.y > 0 && ptr->curr.x < ptr->width && ptr->curr.y < ptr->height)
			illuminate(ptr, color);
		index++;
	}
}

static void	draw_horizontal(t_param *ptr)
{
	int x;
	int y;
	t_points *temp;
	double temp_s;
	double temp_e;

	temp_s = ptr->start.y;
	temp_e = ptr->end.y;
	x = 0;
	temp = malloc(sizeof(t_points));
	while (x < ptr->map_width)
	{
		ptr->start.y = temp_s;
		ptr->end.y = temp_e;
		y = 0;
		while (y < ptr->map_height)
		{
			ptr->end.z = ptr->map[y == ptr->map_height ? y - 1 : y][x == ptr->map_width ? x - 1 : x] * ptr->depth;
			*temp = ptr->end;
			rotate(ptr);
			y != 0 ? draw_line_3d(ptr, ptr->end.z != 0 ? get_color(ptr) : ptr->start_rgb) : 0;
			ptr->start = ptr->end;
			ptr->end = *temp;
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
	int x;
	int y;
	t_points *temp;
	double temp_s;
	double temp_e;

	temp_s = ptr->start.x;
	temp_e = ptr->end.x;
	y = 0;
	temp = malloc(sizeof(t_points));
	while (y < ptr->map_height)
	{
		ptr->start.x = temp_s;
		ptr->end.x = temp_e;
		x = 0;
		while (x < ptr->map_width)
		{
			ptr->end.z = ptr->map[y == ptr->map_height ? y - 1 : y][x == ptr->map_width ? x - 1 : x] * ptr->depth;
			*temp = ptr->end;
			rotate(ptr);
			x != 0 ? draw_line_3d(ptr, ptr->end.z != 0 ? get_color(ptr) : ptr->start_rgb) : 0;
			ptr->start = ptr->end;
			ptr->end = *temp;
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

void	draw_map(t_param *ptr)
{
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->height);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	draw_horizontal(ptr);
	ptr->end.x = 0;
	ptr->end.y = 0;
	draw_vertical(ptr);
	ptr->end.x = 0;
	ptr->end.y = 0;
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	load_interface(ptr);
}
