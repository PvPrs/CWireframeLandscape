/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_events.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/08 16:08:41 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/08 16:08:42 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx_macos/mlx.h"
#include "../../includes/fdf.h"
#include <stdio.h>
#include <stdlib.h>

int		key_event(keyPressed key, t_param *ptr)
{
	if (key == ESC)
	{
		mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
		exit(1);
	}
	if (key == UP)
		ptr->alpha += 0.0650000;
	if (key == DOWN)
		ptr->beta += 0.0650000;
	if (key == RIGHT)
		ptr->gamma += 0.0650000;
	if (key == LEFT)
		ptr->gamma -= 0.0650000;
	mlx_destroy_image(ptr->mlx_ptr, ptr->img);
	draw_map(ptr);
	return (0);
}
