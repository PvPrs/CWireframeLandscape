//
// Created by Dave Van bochove on 2019-09-08.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
} t_param;

void		load_frame(int size_x, int size_y, char *title);
void		ft_read_map(char *file);

#endif //FDF_FDF_H
