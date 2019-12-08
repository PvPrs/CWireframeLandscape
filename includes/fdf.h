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
	ESC = 53,
	A = 0,
	D = 2,
	PLUS = 69,
	MINUS = 78,
} keyPressed;

typedef enum		e_mouse
{
	LEFT_MOUSE = 1,
	RIGHT_MOUSE = 2,
	MIDDLE = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
} mousePressed;

typedef struct s_lines
{
	char *str;
	int	len;
	int rows;
	struct s_lines *next;
} t_lines;

typedef struct s_points
{
	double x;
	double y;
	double z;
} t_points;

typedef struct s_param
{
	void						*mlx_ptr;
	void						*win_ptr;
	void						*img;
	char						*data_addr;
	int							bits_in_pixel;
	int 						size_line;
	int							endian;
	int							width;
	int							height;
	int							**map;
	int							map_width;
	int							map_height;
	int							rgb;
	int							start_rgb;
	int 						end_rgb;
	double						gamma;
	double						beta;
	double						alpha;
	double						depth;
	double						tile_size;
	double						delta_x;
	double						delta_y;
	double						new_x;
	double						new_y;
	double						new_z;
	t_points					start;
	t_points					end;
	t_points					curr;
	fieldVision					fov;
} t_param;


void		load_frame(char *title, char *map);
int			close_frame(void *ptr);
int			**ft_read_map(char *file, t_param *ptr);
void		init(t_param *ptr);
void		load_interface(t_param *ptr);
int			ft_read(char *file);
int			key_event(keyPressed key, t_param *ptr);
int			mouse_event(int mouse, int x, int y, t_param *ptr);
void		draw_map(t_param *ptr);
void		rot_x(t_param *ptr);
void		rot_y(t_param *ptr);
void		rot_z(t_param *ptr, int z);
void		iso(double *x, double *y, int z);
void		rotate(t_param *ptr, int z);
void		position(t_param *ptr, int flag);
int			get_color(t_param *ptr);

#endif //FDF_FDF_H
