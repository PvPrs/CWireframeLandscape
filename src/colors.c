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

static double percent(double start, double end, double current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int get_light(int start, int end, double percentage)
{
	//printf("rgb: %d, start: %d, end: %d\n", (int)((1 - percentage) * start + percentage * end), start, end);
	return ((int)((1 - percentage) * start + percentage * end));
}

/**
 *
 * @param ptr represents the struct
 * @param delta Represents the current set of delta.
 * @param x Represent the current X coordinate
 * @param y Represents the current Y coordinate
 * @return
 */
int get_color(t_param *ptr)
{
	double  percentage;
	int red;
	int green;
	int blue;

	if (ptr->rgb == ptr->end_rgb)
		return (ptr->rgb);
	if (ptr->delta_x > ptr->delta_y)
		percentage = percent(ptr->start.x, ptr->end.x, ptr->curr.x);
	else
		percentage = percent(ptr->start.y, ptr->end.y, ptr->curr.y);
	//printf("%f, 0x%06x, 0x%06x\n", percentage, ptr->start_rgb, ptr->end_rgb);
	red = get_light((ptr->start_rgb >> 16), (ptr->end_rgb >> 16), percentage);
	green = get_light((ptr->start_rgb >> 8) & 0xFF, (ptr->end_rgb >> 8) & 0xFF, percentage);
	blue = get_light(ptr->start_rgb & 0xFF, ptr->end_rgb & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}