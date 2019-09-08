/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 16:11:27 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/06/13 16:11:31 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_free_array(void **arr)
{
	int index;

	index = 0;
	while (arr[index] != NULL)
	{
		free(arr[index]);
		index++;
	}
	arr = NULL;
}
