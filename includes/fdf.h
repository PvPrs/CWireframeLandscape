/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/08 15:42:38 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/09/08 15:42:40 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
#define FDF_FDF_H

typedef struct s_lines
{
	char *str;
	int count;
	struct s_lines *next;
} t_lines;

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
} t_param;

void		load_frame(int size_x, int size_y, char *title);
int			**ft_read_map(char *file);
int			**sort_map(t_lines *lst, int size, int len);
int			ft_read(char *file);

#endif //FDF_FDF_H
