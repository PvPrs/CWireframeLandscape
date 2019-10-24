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
		illuminate(ptr, 0xE0FFFF);
		index++;
	}
}

/**
 *
 *
 * @param ptr
 * @variable axisFlag represents a flag to represent the current Axis being drawn.
 */

void	draw_map(t_param *ptr)
{
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	draw_horizontal(ptr);
	draw_vertical(ptr);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
}

void	draw_horizontal(t_param *ptr)
{
	int row;
	int col;
	t_points *temp;

	row = 0;
	col = 0;
	temp = malloc(sizeof(t_points));
	while (ptr->map[row] != NULL)
	{
		ptr->start.x = 0;
		while (ptr->map[row][col] != -1)
		{
			ptr->end.x = (ptr->start.x + ptr->zoom);
			ptr->end.y = (ptr->start.y);
			ptr->end.z = ptr->map[row][col];
			*temp = ptr->end;
			rotate(ptr);
			draw_line_3d(ptr);
//			printf("ptr Xend: %d", ptr->end.x);
			position(ptr, 1);
			ptr->start = ptr->end;
			ptr->end = *temp;
			col++;
		}
		ptr->end.y += ptr->zoom;
		ptr->start.y = ptr->end.y;
		col = 0;
		row++;
	}
	ptr->start.x = 0;
}

void	draw_vertical(t_param *ptr)
{
	int row;
	int col;
	t_points *temp;

	row = 0;
	col = 0;
	temp = malloc(sizeof(t_points));
	while (ptr->map[row] != NULL)
	{
		ptr->start.y = 0;
		while (ptr->map[row][col] != -1)
		{
			ptr->end.x = (ptr->start.x);
			ptr->end.y = (ptr->start.y + ptr->zoom);
			ptr->end.z = ptr->map[row][col];
			*temp = ptr->end;
			rotate(ptr);
			draw_line_3d(ptr);
			position(ptr, 1);
			ptr->start = ptr->end;
			ptr->end = *temp;
			col++;
		}
		ptr->end.x += ptr->zoom;
		ptr->start.x = ptr->end.x;
		col = 0;
		row++;
	}
}