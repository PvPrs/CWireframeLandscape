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
		exit(1);
	if (key == UP)
		ptr->alpha += 0.0250000;
	if (key == DOWN)
		ptr->beta += 0.025000;
	if (key == RIGHT)
		ptr->gamma -= 0.0250000;
	if (key == LEFT)
		ptr->gamma += 0.0250000;
	mlx_destroy_image(ptr->mlx_ptr, ptr->img);
	draw_map(ptr);
	load_interface(ptr);
	return (0);
}
