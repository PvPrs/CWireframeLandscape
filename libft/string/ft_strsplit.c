/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 20:34:34 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/01/22 20:34:38 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/libft.h"

static int		ft_get_words(const char *s, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			words++;
		}
	}
	return (words);
}

static char		**arr_gen(char const *s, char c, char **str)
{
	int		index;
	int		w_index;

	w_index = 0;
	index = 0;
	while ((*s != 0) || (s[index] != 0))
	{
		if (*s == c)
			++s;
		while (*s != c && *s != 0)
		{
			++s;
			++index;
			if ((*s == c) || (*s == 0))
			{
				str[w_index] = (char*)malloc(sizeof(char) * index + 1);
				str[w_index] = ft_strncpy(str[w_index], &s[-index], index);
				str[w_index][index] = 0;
				++w_index;
			}
		}
		index = 0;
	}
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * ft_get_words(s, c) + 1);
	if (str == NULL)
		return (NULL);
	str[ft_get_words(s, c)] = NULL;
	str = arr_gen(s, c, str);
	return (str);
}
