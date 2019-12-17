/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 16:37:48 by dvan-boc       #+#    #+#                */
/*   Updated: 2019/12/17 18:11:19 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_event(int mouse, int x, int y, struct s_param *ptr)
{
	if (mouse == LEFT_MOUSE)
	{
		if (x >= 17 && x <= 190 && y >= 27 && y <= 41)
			init(ptr);
		else if (x >= 17 && x <= 190 && y >= 44 && y <= 59)
			ptr->fov = (ptr->fov == ISOMETRIC ? PARALLEL : ISOMETRIC);
		else
			return (0);
	}
	if (mouse == SCROLL_UP)
		ptr->depth += 0.20;
	if (mouse == SCROLL_DOWN)
		ptr->depth -= 0.20;
	mlx_destroy_image(ptr->mlx_ptr, ptr->img);
	draw_map(ptr);
	return (0);
}
