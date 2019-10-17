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
		illuminate(ptr, 0xE0FFFF, absX, absY);
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

/**
 * @todo: Make a modular rotation system that takes in a x, y, z coordinate, and a modular draw line function.
 *
 * @param ptr
 */

void	draw_map(t_param *ptr)
{
	int row;
	int col;

	row = 0;
	col = 0;
	ptr->img = mlx_new_image(ptr->mlx_ptr, ptr->width, ptr->length);
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_in_pixel), &(ptr->size_line), &(ptr->endian));
	while (ptr->map[row] != NULL)
	{
		while (ptr->map[row][col] != -1)
		{
			ptr->x = col;
			ptr->y = row;
			ptr->s_x = col;
			ptr->s_y = row;
			rotate(ptr, ptr->map[row][col]);

			printf("s_x: %d, x: %d - s_y: %d, y: %d\n", ptr->s_x, ptr->x, ptr->s_y, ptr->y);
			draw_line_3d(ptr, ptr->s_x, ptr->s_y, ptr->x, ptr->y + ptr->zoom);
			draw_line_3d(ptr, ptr->s_x, ptr->s_y, ptr->x + ptr->zoom, ptr->y);
			col++;
		}
		col = 0;
		row++;
	}
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img, 0, 0);
}