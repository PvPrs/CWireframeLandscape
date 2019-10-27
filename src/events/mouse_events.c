/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 16:37:48 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/28 16:37:49 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"
#include "../../minilibx_macos/mlx.h"
#include <stdio.h>

int		mouse_event(mousePressed mouse, int x, int y, t_param *ptr)
{
	if (mouse == LEFT_MOUSE)
	{
		if (x >= 17 && x <= 175 && y >= 27 && y <= 41)
			ptr->fov = (ptr->fov == ISOMETRIC ? PARALLEL : ISOMETRIC);
		else
			return (0);
	}
	if (mouse == SCROLL_DOWN)
		ptr->zoom -= 0.20;
	if (mouse == SCROLL_UP)
		ptr->zoom += 0.20;
	mlx_destroy_image(ptr->mlx_ptr, ptr->img);
	draw_map(ptr);
	return (0);
}

int mouse_move(int x, int y, t_param *ptr)
{
	(void)ptr;
	x = 0;
	y = 0;
//	printf("mouse X: %d, mouse Y: %d", x, y);
	return (0);
}
