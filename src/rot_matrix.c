/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rot_matrix.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 15:24:20 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/10/17 15:24:27 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>
#include <stdio.h>

void	rot_z(double *x, double *y, double gamma)
{
	*x = *x * cos(gamma) - sin(gamma) * *y;
	*y = *x * sin(gamma) + *y * cos(gamma);
}

void	rot_x(double *y, double *z, double alpha)
{
	*y = *y * cos(alpha) - *z * sin(alpha);
	*z = sin(alpha) * (*y) + cos(alpha) * (*z);
}

void	rot_y(double *x, double *z, double beta)
{
	*x = *x * cos(beta) + sin(beta) * (*z);
	*z = -sin(beta) * (*x) + cos(beta) * (*z);
}

void	position(t_param *ptr, int flag)
{
	if (flag == 0)
	{
		ptr->start.x += (ptr->width - (ptr->tile_size * (ptr->map_width / 2))) / 2;
		ptr->start.y += (ptr->height - (ptr->tile_size * (ptr->map_height / 2))) / 2;
		ptr->end.x += (ptr->width - (ptr->tile_size * (ptr->map_width / 2))) / 2;
		ptr->end.y += (ptr->height - (ptr->tile_size * (ptr->map_height / 2))) / 2;
	}
	else
	{
		ptr->start.x -= (ptr->width - (ptr->tile_size * (ptr->map_width / 2))) / 2;
		ptr->start.y -= (ptr->height - (ptr->tile_size * (ptr->map_height / 2))) / 2;
		ptr->end.x -= (ptr->width - (ptr->tile_size * (ptr->map_width / 2))) / 2;
		ptr->end.y -= (ptr->height - (ptr->tile_size * (ptr->map_height / 2))) / 2;
	}
}

void	rotate(t_param *ptr)
{
	position(ptr, 0);
	rot_z(&ptr->end.x, &ptr->end.y, ptr->gamma);
	rot_x(&ptr->end.y, &ptr->end.z, ptr->alpha);
	rot_y(&ptr->end.x, &ptr->end.z, ptr->beta);
//	ptr->start.x += (ptr->width / 2);
//	ptr->start.y += ptr->length / 2;
//	ptr->end.x += (ptr->width / 2);
//	ptr->end.y += ptr->length / 2;

}
