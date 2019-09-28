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

typedef enum		e_keys
{
	LEFT = 123,
	RIGHT = 124,
	DOWN = 125,
	UP = 126,
	ESC = 53
} keyPressed;

typedef enum		e_mouse
{
	LEFT_B = 1,
	RIGHT_B = 2,
	MIDDLE_B = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
} mousePressed;

typedef struct		s_dim
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_dim;

void		load_frame(int size_x, int size_y, char *title, int **map);
int			**ft_read_map(char *file);
int			**sort_map(t_lines *lst, int size, int len);
int			ft_read(char *file);
void		draw_line_3d(char **map, t_param *ptr);
int			key_event(keyPressed key, t_param *mlx);


#endif //FDF_FDF_H
