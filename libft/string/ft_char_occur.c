/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char_occur.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 16:40:13 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/13 16:40:45 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** @param str Represents the String to search in
** @param occur Represents the character to find
** @param term_char Represents the terminating character
** @return
*/

int		ft_char_occur(char *str, char occur)
{
	int index;
	int count;

	count = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == occur)
			count++;
		index++;
	}
	return (count);
}
