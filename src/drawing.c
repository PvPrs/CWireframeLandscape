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

	xAxis = ptr->points.startX;
	yAxis = ptr->points.startY;
	if (xAxis >= 0 && xAxis <= ptr->width && yAxis >= 0 && yAxis <= ptr->length)
	{
		index = (xAxis * ptr->bits_in_pixel / 8) + (yAxis * ptr->size_line);
		ptr->data_addr[index] = color; // B — Blue
		index++;
		ptr->data_addr[index] = color >> 8; // G — Green
		index++;
		ptr->data_addr[++index] = color >> 16; // R — Red
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
void	draw_line_3d(t_param *ptr)
{
	int deltaX;
	int deltaY;
	int leadAxis;
	int index_x;
	int index;
	int index_y;

	deltaX = abs(ptr->points.endX - ptr->points.startX);
	deltaY = abs(ptr->points.endY - ptr->points.startY);
	leadAxis = deltaX > deltaY ? deltaX : deltaY;
	index_x = ptr->points.endX >= ptr->points.startX ? 1 : -1;
	index_y = ptr->points.endY >= ptr->points.startY ? 1 : -1;
	index = leadAxis;
	ptr->points.endX = ptr->points.endY = leadAxis / 2; /* error offset */
	while(1)
	{
		illuminate(ptr, 0xE0FFFF);
		if (index-- == 0)
			break;
		ptr->points.endX -= deltaX;
		if (ptr->points.startX <= ptr->points.endX)
		{
			ptr->points.endX += index_x;
			ptr->points.startX++;
		}
		ptr->points.endY -= deltaY;
		if (ptr->points.startX <= ptr->points.endX)
		{
			ptr->points.endY += index_y;
			ptr->points.startY++;
		}
	}
}

//void		ft_bresenham(t_data *data, t_pixel *p0, t_pixel *p1)
//{
//	t_draw	draw;
//
//	draw.dx = fabs(p1->x - p0->x);
//	draw.dy = fabs(p1->y - p0->y);
//	draw.sx = p1->x >= p0->x ? 1 : -1;
//	draw.sy = p1->y >= p0->y ? 1 : -1;
//	if (draw.dy <= draw.dx)
//	{
//		draw.d = (draw.dy << 1) - draw.dx;
//		draw.d1 = draw.dy << 1;
//		draw.d2 = (draw.dy - draw.dx) << 1;
//		ft_horizontal(data, p0, p1, draw);
//	}
//	else
//	{
//		draw.d = (draw.dx << 1) - draw.dy;
//		draw.d1 = draw.dx << 1;
//		draw.d2 = (draw.dx - draw.dy) << 1;
//		ft_vertical(data, p0, p1, draw);
//	}
//}


/**
 *
 *
 * @param ptr
 * @variable axisFlag represents a flag to represent the current Axis being drawn.
 */

void	draw_map(t_param *ptr)
{
	int row;
	int col;
	int axisFlag;

	axisFlag = 0;
	row = 0;
	col = 0;
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	while (ptr->map[row] != NULL)
	{
		while (ptr->map[row][col] != -1)
		{
			ptr->points.startX = col * ptr->zoom;
			ptr->points.startY = row * ptr->zoom;
			ptr->points.endX = axisFlag == X ? (col * ptr->zoom) + ptr->zoom : ptr->points.startX;
			ptr->points.endY = axisFlag == Y ? (row * ptr->zoom) + ptr->zoom : ptr->points.startY;
			ptr->points.z = ptr->map[row][col] * ptr->zoom;
			printf("flag: %d, start: %d, %d - end %d, %d\n", axisFlag, ptr->points.startX, ptr->points.startY, ptr->points.endX, ptr->points.endY);
			rotate(ptr);
			draw_line_3d(ptr);
			if (axisFlag == Y)
			{
				axisFlag = X;
				continue;
			}
			col++;
			axisFlag = Y;
		}
		printf("row: %d\n", row);
		col = 0;
		row++;
	}
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
}
///**
// * @todo: Make a modular rotation system that takes in a x, y, z coordinate, and a modular draw line function.
// *
// * @param ptr
// */
//
//void	draw_map(t_param *ptr)
//{
//	int row;
//	int col;
//
//	row = 0;
//	col = 0;
//	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
//	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
//	while (ptr->map[row] != NULL)
//	{
//		while (ptr->map[row][col] != -1)
//		{
//			ptr->x = col * ptr->zoom;
//			ptr->y = row * ptr->zoom;
//			ptr->z = ptr->map[row][col] * ptr->zoom;
//			rotate(ptr);
//			draw_line_3d(ptr, ptr->x, ptr->y, ptr->x, ptr->y + ptr->zoom);
//			draw_line_3d(ptr, ptr->x, ptr->y, ptr->x + ptr->zoom, ptr->y);
//			col++;
//		}
//		col = 0;
//		row++;
//	}
//	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
//}