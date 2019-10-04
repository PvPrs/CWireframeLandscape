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


void		illuminate(t_param *ptr, int color, int x, int y)
{
	int index;

	index = (x * ptr->bits_in_pixel / 8) + (y * ptr->size_line);
	ptr->data_addr[index] = color; // B — Blue
	ptr->data_addr[++index] = color >> 8; // G — Green
	ptr->data_addr[++index] = color >> 16; // R — Red
	ptr->data_addr[++index] = 0; // Alpha channel
}

/**
 * Rersources for Bresenham Algorithm
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * http://graphics.idav.ucdavis.edu/education/GraphicsNotes/Bresenhams-Algorithm.pdf - good Explanation
 * http://members.chello.at/~easyfilter/bresenham.html - sample code
 * @param absX
 * @param absY
 * @param absZ
 */
void	draw_line_3d(t_param *ptr, int absX, int absY, int absXEnd, int absYEnd)
{
	int DeltaX = absXEnd - absX;
	int DeltaY = absYEnd - absY;
	int leadAxis = DeltaX > DeltaY ? DeltaX : DeltaY;
	int index = leadAxis; /* maximum difference */
	absXEnd = absYEnd = leadAxis / 2; /* error offset */

	while(1)
	{
		illuminate(ptr, 0xEC4B27, absX, absY);
		if (index-- == 0)
			break;
		absXEnd -= DeltaX;
		if (absXEnd < 0)
		{
			absXEnd += leadAxis;
			absX++;
		}
		absYEnd -= DeltaY;
		if (absYEnd < 0)
		{
			absYEnd += leadAxis;
			absY++;
		}
	}
}

void	draw_map(t_param *ptr)
{
	int row;
	int col;
	int width;

	row = 0;
	col = 0;
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
	while (ptr->map[row] != NULL)
	{
		while (ptr->map[row][col] != -1)
		{
			width = 1; //TODO: must be a variable;
			ptr->x = row;
			ptr->y = col;
			rotate(ptr, ptr->map[row][col]);
			draw_line_3d(ptr, ptr->x * width, ptr->y * width, (ptr->x + 1) * width, ptr->y * width);
			draw_line_3d(ptr, ptr->x * width, ptr->y * width, ptr->x * width, (ptr->y + 1) * width);
			col++;
		}
		col = 0;
		row++;
	}
}