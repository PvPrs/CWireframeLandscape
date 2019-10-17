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
	ptr->x += ptr->width / 4;
	ptr->y += ptr->length / 4;
}

void	rotate(t_param *ptr)
{
	rot_z(&ptr->x, &ptr->y, ptr->gamma);
	rot_x(&ptr->y, &ptr->z, ptr->alpha);
	rot_y(&ptr->x, &ptr->z, ptr->beta);
	center(ptr);
}
