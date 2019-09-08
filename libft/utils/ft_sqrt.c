/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 13:51:21 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/02/03 13:51:22 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define NEXT(n, i)  (((n) + (i)/(n)) >> 1)

unsigned int	ft_sqrt(unsigned int number)
{
	unsigned int n;
	unsigned int n1;

	n = 1;
	n1 = NEXT(n, number);
	while ((n1 - n) > 1)
	{
		n = n1;
		n1 = NEXT(n, number);
	}
	while (n1 * n1 > number)
		n1--;
	return (n1);
}
