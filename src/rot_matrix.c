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

void	rot_z(int *x, int *y, double gamma)
{
	*x = (*x * cos(gamma) - sin(gamma) * *y);
	*y = (*x * sin(gamma) + *y * cos(gamma));
}

void	rot_x(int *y, int *z, double alpha)
{
	*y = *y * cos(alpha) - *z * sin(alpha);
	*z = sin(alpha) * (*y) + cos(alpha) * (*z);
}

void	rot_y(int *x, int *z, double beta)
{
	*x = *x * cos(beta) + sin(beta) * (*z);
	*z = -sin(beta) * (*x) + cos(beta) * (*z);
}

void	center(t_param *ptr)
{
	ptr->points.startX += ptr->width / 4;
	ptr->points.startY += ptr->length / 4;
	ptr->points.endX += ptr->width / 4;
	ptr->points.endY += ptr->length / 4;
}

void	rotate(t_param *ptr)
{
	rot_z(&ptr->points.endX, &ptr->points.endY, ptr->gamma);
	rot_x(&ptr->points.endY, &ptr->points.z, ptr->alpha);
	rot_y(&ptr->points.endX, &ptr->points.z, ptr->beta);
	center(ptr);
}
