/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 16:53:10 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/01/18 16:53:13 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	str[len];
	int		index;
	int		index_2;
	char	*ptr;

	ptr = str;
	index = start;
	index_2 = 0;
	if (!s)
		return (NULL);
	while (s[index] && len != 0)
	{
		str[index_2] = s[index];
		index++;
		index_2++;
		len--;
	}
	return (ptr);
}
