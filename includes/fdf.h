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
	int	len;
	int rows;
	struct s_lines *next;
} t_lines;

typedef enum		e_projection
{
	PARALLEL,
	ISOMETRIC
} fieldVision;

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
	LEFT_MOUSE = 1,
	RIGHT_MOUSE = 2,
	MIDDLE = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
} mousePressed;

typedef struct s_param
{
	int length;
	int width;
	fieldVision					fov;
	double						zoom;
	int							add;
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
	int							len;
	int							size;
	int							y;
	int							x;
	int							z;
	int							s_y;
	int							s_x;
	int							s_z;
	int							new_y;
	int							new_x;
	int							new_z;
} t_param;

typedef struct		s_dim
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_dim;

void		load_frame(char *title, char *map);
int			close_frame(void *ptr);
int			**ft_read_map(char *file);
void		init(t_param *ptr, char *map);
void		load_interface(t_param *ptr);
int			**sort_map(t_lines *lst, int size, int len);
int			ft_read(char *file);
int			key_event(keyPressed key, t_param *ptr);
int			mouse_event(mousePressed mouse, int x, int y, t_param *ptr);
void		draw_line_3d(t_param *ptr, int absX, int absY, int absXEnd, int absYEnd);
void		illuminate(t_param *ptr, int color, int x, int y);
void		draw_map(t_param *ptr);
void		rot_x(t_param *ptr);
void		rot_y(t_param *ptr);
void		rot_z(t_param *ptr, int z);
void		rotate(t_param *ptr, int z);
int			mouse_move(int x, int y, t_param *ptr);

#endif //FDF_FDF_H
