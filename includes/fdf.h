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
# define FDF_FDF_H

enum					e_color
{
	DEFAULT = 0xff9c33,
	CANARY_YELLOW = 0xd7ff33,
	LIGHT_GREEN = 0x9cff33,
	LIME_GREEN = 0x00FF00,
	WHITE = 0xFFFFFF,
	LIGHT_ORANGE = 0xff5e33,
	ORANGE = 0xff4633,
	RED = 0xFF0000
};

enum	e_projection
{
	PARALLEL,
	ISOMETRIC
};

enum					e_keys
{
	LEFT = 123,
	RIGHT = 124,
	DOWN = 125,
	UP = 126,
	ESC = 53,
	A = 0,
	D = 2,
	PLUS = 24,
	MINUS = 27,
	PLUS_NUM = 69,
	MINUS_NUM = 78
};

enum					e_mouse
{
	LEFT_MOUSE = 1,
	RIGHT_MOUSE = 2,
	MIDDLE = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

struct					s_lines
{
	char				*str;
	int					len;
	int					rows;
	struct s_lines		*next;
};

struct					s_points
{
	int					x;
	int					y;
	int					z;
	int					rgb;
};

struct					s_param
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img;
	char				*data_addr;
	int					bits_in_pixel;
	int					size_line;
	int					endian;
	int					width;
	int					height;
	int					**map;
	int					map_width;
	int					map_height;
	double				gamma;
	double				beta;
	double				alpha;
	double				depth;
	int					tile_size;
	int					delta_x;
	int					delta_y;
	int					new_x;
	int					new_y;
	int					new_z;
	struct s_points		start;
	struct s_points		end;
	struct s_points		curr;
	enum e_projection	fov;
};

void			load_frame(char *title, char *map);
int				close_frame(struct s_param *ptr);
int				**ft_read_map(char *file, struct s_param *ptr);
void			init(struct s_param *ptr);
void			load_interface(struct s_param *ptr);
int				ft_read(char *file);
int				key_event(enum e_keys key, struct s_param *ptr);
int				mouse_event(int mouse, int x, int y, struct s_param *ptr);
void			draw_map(struct s_param *ptr);
void			rot_x(struct s_param *ptr);
void			rot_y(struct s_param *ptr);
void			rot_z(struct s_param *ptr, int z);
void			iso(int *x, int *y, int z);
void			rotate(struct s_param *ptr, int z);
void			position(struct s_param *ptr, int flag);
int				get_color(struct s_param *ptr);
enum e_color	get_default_color(int z);

#endif
