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
#include <math.h>

void	draw_Line(int absX, int absY, int absX_1, int absY_1)
{
	int dy = -ft_abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */
	int dx;
	dx = ft_abs(x1-x0)
	sx = x0<x1 ? 1 : -1;

	for(;;){  /* loop */
		setPixel(x0,y0);
		if (x0==x1 && y0==y1) break;
		e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

/**
 * Calculates the differnce between the 2 coordinates
 * @param coord
 * @param coord_2
 * @return absolute integer
 */
int calc_delta(int coord, int coord_2)
{
	return (abs(coord_2 - coord));
}

/**
 * Rersources for Bresenham Algorithm
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * http://graphics.idav.ucdavis.edu/education/GraphicsNotes/Bresenhams-Algorithm.pdf - good Explanation
 * @param absX
 * @param absY
 * @param absZ
 */
void	draw_line_3d(int absX, int absY, int absZ)
{
	int DeltaX = ft_abs(x1-x0);
	int sx = x0<x1 ? 1 : -1;
	int DeltaY = ft_abs(y1-y0);
	int sy = y0<y1 ? 1 : -1;
	int deltaZ = ft_abs(z1-z0);
	int sz = z0<z1 ? 1 : -1;
	int dm = max(dx,dy,dz);
	int i = dm; /* maximum difference */
	x1 = y1 = z1 = dm/2; /* error offset */

	for(;;) {  /* loop */
		setPixel(x0,y0,z0);
		if (i-- == 0) break;
		x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; }
		y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; }
		z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; }
	}
}