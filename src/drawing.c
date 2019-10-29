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

void		illuminate(t_param *ptr, int color)
{
	int index;
	int xAxis;
	int yAxis;

	xAxis = ptr->start.x;
	yAxis = ptr->start.y;
	if (xAxis >= 0 && xAxis <= ptr->width && yAxis >= 0 && yAxis <= ptr->length)
	{
		index = (xAxis * ptr->size_line) + (yAxis * ptr->bits_in_pixel / 8);
		ptr->data_addr[index] = color; // B — Blue
		index++;
		ptr->data_addr[index] = color >> 8; // G — Green
		index++;
		ptr->data_addr[index] = color >> 16; // R — Red
		index++;
		ptr->data_addr[index] = 10; // Alpha channel
	}
}

/**
 * Rersources for Bresenham Algorithm
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * http://graphics.idav.ucdavis.edu/education/GraphicsNotes/Bresenhams-Algorithm.pdf - good Explanation
 * http://members.chello.at/~easyfilter/bresenham.html - sample code
 * @param absX
 * @param absY
 * @param absZ
 * @TODO: This bresenham algo needs fixing and is the cause of the incorrect drawing.
 */
void		draw_line_3d(t_param *ptr)
{
	double deltaX;
	double deltaY;
	double leadAxis;
	double xincrement;
	double index;
	double yincrement;
	printf("start: %f, %f   end: %f, %f\n", ptr->start.x, ptr->start.y, ptr->end.x, ptr->end.y);

	index = 0;
	deltaX = ptr->end.x - ptr->start.x;
	deltaY = ptr->end.y - ptr->start.y;
	leadAxis = fabs(deltaX) > fabs(deltaY) ? deltaX : deltaY;
	xincrement = deltaX / (float) leadAxis;
	yincrement = deltaY / (float) leadAxis;
	while (index < leadAxis)
	{
		ptr->start.x += xincrement;
		ptr->start.y += yincrement;
		if (ptr->start.x > 0 && ptr->start.y > 0 && ptr->start.x < ptr->width && ptr->start.y < ptr->length)
			illuminate(ptr, 0xE0FFFF);
		index++;
	}
}

/**
 * draw_map initializes andd sets up the complete drawing of the map.
 * @param ptr
 * @variable axisFlag represents a flag to represent the current Axis being drawn.
 */

void	draw_map(t_param *ptr)
{
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	draw_horizontal(ptr);
	ptr->start.x = 0;
	ptr->start.y = 0;
	ptr->end.x = 0;
	ptr->end.y = 0;
	draw_vertical(ptr);
	ptr->start.x = 0;
	ptr->start.y = 0;
	ptr->end.x = 0;
	ptr->end.y = 0;
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	load_interface(ptr);
}

void	draw_horizontal(t_param *ptr)
{
	int x;
	int y;
	t_points *temp;
	double tempx;
	double tempx2;

	tempx = ptr->start.x;
	tempx2 = ptr->end.x;
	y = 0;
	temp = malloc(sizeof(t_points));
	while (y < ptr->map_width)
	{
		ptr->start.x = tempx;
		ptr->end.x = tempx2;
		x = 0;
		while (x < ptr->map_height)
		{
			ptr->end.z = ptr->map[x == ptr->map_height ? x - 1 : x][y == ptr->map_height ? y - 1 : y] * ptr->depth;
			*temp = ptr->end;
			rotate(ptr);
			draw_line_3d(ptr);
			position(ptr, 1);
			ptr->start = ptr->end;
			ptr->end = *temp;
			ptr->end.x += ptr->zoom;
			x++;
		}
		ptr->end.y += ptr->zoom;
		ptr->start.y = ptr->end.y;
		y++;
	}
	printf("x: %f y: %f, endX: %f, endY: %f\n", ptr->start.x, ptr->start.y, ptr->end.x, ptr->end.y);
}

void	draw_vertical(t_param *ptr)
{
	int x;
	int y;
	t_points *temp;
	double tempy;
	double tempy2;

	tempy = ptr->start.y;
	tempy2 = ptr->end.y;
	x = 0;
	temp = malloc(sizeof(t_points));
	while (x < ptr->map_height)
	{
		ptr->start.y = tempy;
		ptr->end.y = tempy2;
		y = 0;
		while (y < ptr->map_width)
		{
			//ptr->end.y = (ptr->start.y + ptr->zoom);
			ptr->end.z = ptr->map[x == ptr->map_height ? x - 1 : x][y == ptr->map_height ? y - 1 : y] * ptr->depth;
			*temp = ptr->end;
			rotate(ptr);
			draw_line_3d(ptr);
			position(ptr, 1);
			ptr->start = ptr->end;
			ptr->end = *temp;
			ptr->end.y += ptr->zoom;
			y++;
		}
		ptr->end.x += ptr->zoom;
		ptr->start.x = ptr->end.x;
		x++;
	}
	printf("x: %f y: %f, endX: %f, endY: %f\n", ptr->start.x, ptr->start.y, ptr->end.x, ptr->end.y);
}