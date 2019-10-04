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
	int length;
	int width;
	int zoom;
	int add;
	int							**map;
	void						*mlx_ptr;
	void						*win_ptr;
	void						*img;
	char						*data_addr;
	double						gamma;
	double						beta;
	double						alpha;
	int							bits_in_pixel;
	int 						size_line;
	int							endian;
	int							y;
	int							x;
	int							z;
	int							new_y;
	int							new_x;
	int							new_z;
} t_param;

typedef struct s_field_of_vision
{
	int grid_width;
	int zoom;
	int rot_x;
	int rot_y;
} t_FoV;

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

void		init(t_param *ptr, char *map);
void		load_frame(char *title, char *map);
int			**ft_read_map(char *file);
int			**sort_map(t_lines *lst, int size, int len);
int			ft_read(char *file);
int			key_event(keyPressed key, t_param *ptr);
void		draw_line_3d(t_param *ptr, int absX, int absY, int absXEnd, int absYEnd);
void		illuminate(t_param *ptr, int color, int x, int y);
void		draw_map(t_param *ptr);
void		rot_x(t_param *ptr);
void		rot_y(t_param *ptr);
void		rot_z(t_param *ptr, int z);
void		rotate(t_param *ptr, int z);

#endif //FDF_FDF_H
