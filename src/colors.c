/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 11:15:42 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/10/31 11:16:11 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/fdf.h"

static double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

/*
** Gets the colors depending on the altitude of the current position.
** @param ptr represents the struct
** @return the integer value represented in RGB hexadecimal.
*/

int				get_color(struct s_param *ptr)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (ptr->curr.rgb == ptr->end.rgb)
		return (ptr->curr.rgb);
	if (ptr->delta_x > ptr->delta_y)
		percentage = percent(ptr->start.x, ptr->end.x, ptr->curr.x);
	else
		percentage = percent(ptr->start.y, ptr->end.y, ptr->curr.y);
	red = get_light((ptr->start.rgb >> 16), (ptr->end.rgb >> 16), percentage);
	green = get_light((ptr->start.rgb >> 8) & 0xFF, (ptr->end.rgb >> 8) & 0xFF,
			percentage);
	blue = get_light(ptr->start.rgb & 0xFF, ptr->end.rgb & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

/*
** Get the default color for the entire tile on top.
 * Color depends on altitude of current position.
*/

enum e_color			get_default_color(int z)
{
	double	percentage;

	percentage = percent(-100, 100, z);
	if (percentage < 0.1)
		return (RED);
	else if (percentage < 0.3)
		return (ORANGE);
	else if (percentage < 0.5)
		return (LIGHT_ORANGE);
	else if (percentage == 0.5)
		return (DEFAULT);
	else if (percentage < 0.6)
		return (CANARY_YELLOW);
	else if (percentage < 0.8)
		return (LIGHT_GREEN);
	else
		return (LIME_GREEN);
}
