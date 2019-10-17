/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation_matrix.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 15:14:43 by rvan-ket       #+#    #+#                */
/*   Updated: 2019/05/23 20:16:16 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>
#include <stdio.h>

void	rot_z(int *x, int *y, double gamma)
{
	*x = (*x * cos(gamma) - sin(gamma) * *y) * 20;
	*y = (*x * sin(gamma) + *y * cos(gamma)) * 20;
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
//	ptr->s_x *= ptr->zoom;
//	ptr->s_y *= ptr->zoom;
//	ptr->s_z *= ptr->zoom;
//	ptr->s_x += ptr->width / 3;
//	ptr->s_y += ptr->length / 3;
	ptr->x += ptr->width / 4;
	ptr->y += ptr->length / 4;
}

void	rotate(t_param *ptr)
{
//	ptr->x -= ptr->add * ptr->width / 2;
//	ptr->y -= ptr->add * ptr->length / 2;
	rot_z(&ptr->x, &ptr->y, ptr->gamma);
	ptr->z *= ptr->zoom;
	rot_x(&ptr->y, &ptr->z, ptr->alpha);
	rot_y(&ptr->x, &ptr->z, ptr->beta);
	center(ptr);
}
