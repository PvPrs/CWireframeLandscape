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

void	rot_z(t_param *ptr, int z)
{
	ptr->new_x = (ptr->x * cos(ptr->gamma) - sin(ptr->gamma) * ptr->y) * ptr->zoom;
	ptr->new_y = (ptr->x * sin(ptr->gamma) + ptr->y * cos(ptr->gamma) * ptr->zoom);
	ptr->new_z = z * ptr->zoom;
}

void	rot_x(t_param *ptr)
{
	double new_y;
	double new_z;

	new_y = ptr->new_y * cos(ptr->alpha) - ptr->new_z * sin(ptr->alpha);
	new_z = sin(ptr->alpha) * ptr->new_y + cos(ptr->alpha) * ptr->new_z;
	ptr->new_y = new_y;
	ptr->new_z = new_z;
}

void	rot_y(t_param *ptr)
{
	double new_x;
	double new_z;

	new_x = ptr->new_x * cos(ptr->beta) + sin(ptr->beta) * ptr->new_z;
	new_z = -sin(ptr->beta) * ptr->new_x + cos(ptr->beta) * ptr->new_z;
	ptr->new_x = new_x;
	ptr->new_z = new_z;
}

void	center(t_param *ptr)
{
	ptr->s_x *= ptr->zoom;
	ptr->s_y *= ptr->zoom;
	ptr->s_z *= ptr->zoom;
	ptr->s_x += ptr->width / 3;
	ptr->s_y += ptr->length / 3;
	ptr->x += ptr->width / 3;
	ptr->y += ptr->length / 3;
}

void	rotate(t_param *ptr, int z)
{
//	ptr->x -= ptr->add * ptr->width / 2;
//	ptr->y -= ptr->add * ptr->length / 2;
	rot_z(ptr, z);
	rot_x(ptr);
	rot_y(ptr);
	ptr->x = ptr->new_x;
	ptr->y = ptr->new_y;
	ptr->z = ptr->new_z;
	center(ptr);
}
