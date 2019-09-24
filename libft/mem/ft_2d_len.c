/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_2d_len.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 16:39:44 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/10 16:39:45 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*
** Returns the amount of rows contained in a 2D Array
** @return
*/
int		ft_2d_len(char **arr)
{
	int index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}