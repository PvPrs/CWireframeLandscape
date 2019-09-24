/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 18:58:11 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/02/04 18:58:12 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

int		get_next_line(const int fd, char **line);
#endif