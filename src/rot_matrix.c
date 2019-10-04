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
	ptr->new_x = ptr->x * cos(ptr->gamma) - sin(ptr->gamma) * ptr->y;
	ptr->new_y = ptr->x * sin(ptr->gamma) + ptr->y * cos(ptr->gamma);
	ptr->new_z = z;
	ptr->new_x = ptr->new_x * ptr->zoom;
	ptr->new_y = ptr->new_y * ptr->zoom;
	ptr->new_z = ptr->new_z * ptr->zoom;
}

void	rot_x(t_param *ptr)
{
	double new_x;
	double new_y;
	double new_z;

	new_x = ptr->new_x;
	new_y = ptr->new_y * cos(ptr->alpha) - ptr->new_z * sin(ptr->alpha);
	new_z = sin(ptr->alpha) * ptr->new_y + cos(ptr->alpha) * ptr->new_z;
	ptr->new_x = new_x;
	ptr->new_y = new_y;
	ptr->new_z = new_z;
}

void	rot_y(t_param *ptr)
{
	double new_x;
	double new_y;
	double new_z;

	new_x = ptr->new_x * cos(ptr->beta) + sin(ptr->beta) * ptr->new_z;
	new_y = ptr->new_y;
	new_z = -sin(ptr->beta) * ptr->new_x + cos(ptr->beta) * ptr->new_z;
	ptr->new_x = new_x;
	ptr->new_y = new_y;
	ptr->new_z = new_z;
}

void	rotate(t_param *ptr, int z)
{
	printf("gets here 1\n");
//	ptr->x -= ptr->add * ptr->x / 2;
//	ptr->y -= ptr->add * ptr->y / 2;
	rot_z(ptr, z);
	rot_x(ptr);
	rot_y(ptr);
	printf("gets here 1\n");
	ptr->x = ptr->new_x;
	ptr->y = ptr->new_y;
	ptr->z = ptr->new_z;
	ptr->x += ptr->length / 4;
	ptr->y += ptr->width / 4;
	printf("x: %d y: %d\n", ptr->x, ptr->y);
}
