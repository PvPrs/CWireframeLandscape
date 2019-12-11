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

void	rot_z(t_param *ptr, int z)
{
	ptr->new_x = ptr->end.x * cos(ptr->gamma) - sin(ptr->gamma) * ptr->end.y;
	ptr->new_y = ptr->end.x * sin(ptr->gamma) + ptr->end.y * cos(ptr->gamma);
	ptr->new_z = z * ptr->depth;
}

void	rot_x(t_param *ptr)
{
	int new_x;
	int new_y;
	int new_z;

	new_x = ptr->new_x;
	new_y = ptr->new_y * cos(ptr->alpha) - ptr->new_z * sin(ptr->alpha);
	new_z = sin(ptr->alpha) * ptr->new_y + cos(ptr->alpha) * ptr->new_z;
	ptr->new_x = new_x;
	ptr->new_y = new_y;
	ptr->new_z = new_z;
}

void	rot_y(t_param *ptr)
{
	int new_x;
	int new_y;
	int new_z;

	new_x = ptr->new_x * cos(ptr->beta) + sin(ptr->beta) * ptr->new_z;
	new_y = ptr->new_y;
	new_z = -sin(ptr->beta) * ptr->new_x + cos(ptr->beta) * ptr->new_z;
	ptr->new_x = new_x;
	ptr->new_y = new_y;
	ptr->new_z = new_z;
}

void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	rotate(t_param *ptr, int z)
{
	ptr->end.x -= ptr->tile_size * (ptr->map_width / 2);
	ptr->end.y -= ptr->tile_size * (ptr->map_height / 2);
	rot_z(ptr, z);
	rot_x(ptr);
	rot_y(ptr);
	ptr->end.x = ptr->new_x;
	ptr->end.y = ptr->new_y;
	ptr->end.z = ptr->new_z;
	if (ptr->fov == ISOMETRIC)
		iso(&ptr->end.x, &ptr->end.y, ptr->end.z);
	ptr->end.x += ptr->width / 2;
	ptr->end.y += ptr->height / 2;
}
