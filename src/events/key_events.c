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

int		key_event(keyPressed key, t_param *mlx)
{
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(1);
	}
	return (0);
}
