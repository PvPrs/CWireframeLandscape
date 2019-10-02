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

///**
// * Calculates the differnce between the 2 coordinates
// * @param coord
// * @param coord_2
// * @return absolute integer
// */
//int calc_delta(int coord, int coord_2)
//{
//	return (abs(coord_2 - coord));
//}

void		set_gradient(t_param *ptr, int color, int x, int y)
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
void	draw_line_3d(int absX, int absXEnd, int absY, int absYEnd, t_param *ptr)
{
	int DeltaX = absX - absXEnd;
	int DeltaY = absYEnd - absY;
	int dm = DeltaX > DeltaY ? DeltaX : DeltaY;
	int i = dm; /* maximum difference */
	printf("%d\n", i);
	absXEnd = absYEnd = dm/2; /* error offset */

	while(1)
	{
		printf("%d\n", i);
		set_gradient(ptr, 0xEC4B27, absX, absY);
		if (i-- == 0)
			break;
		absXEnd -= DeltaX;
		if (absXEnd < 0)
		{
			absXEnd += dm;
			absX++;
		}
		absYEnd -= DeltaY;
		if (absYEnd < 0)
		{
			absYEnd += dm;
			absY++;
		}
	}
}