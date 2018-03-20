/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   FdF.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/12 18:35:39 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/12 18:35:39 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# define MAP (params.map)

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../Minilibx/mlx.h"
#include "../Libft/Includes/libft.h"

typedef struct	s_pos
{
	int	z;
	int	y;
	int x;
}				t_pos;

typedef struct	s_draw
{
	t_pos s_win;
	t_pos a;
	t_pos b;
	int	xinc;
	int	yinc;
	int size;
	int count;
	int	col_a;
	int	col_b;
	int dis_x;
	int dis_y;
}				t_draw;

typedef struct	s_map
{
	t_pos	*line_y;
	t_pos	*line_x;
	t_pos	coord;
	int		color;
	int		stop;
}				t_map;

typedef struct	s_fdf
{
	char	***file_map;
	void	*mlx_img;
	int		s_line;
	t_pos	center;
	t_map	**map;
	t_pos	s_win;
	t_pos	s_map;
}				t_fdf;

typedef struct	s_mlx
{
	void	*win_ptr;
	void	*img_ptr;
	void	*mlx_ptr;
	int		endian;
	int 	bpp;
	int		s_l;
}				t_mlx;

// Bordel

t_pos		fill_pos(int y, int x);
void	put_pixel_image(char *mlx_img, t_draw info, int cur);
void	put_pixel_black(t_fdf *params, t_pos print, int max);
void	delete_background_line_x(t_fdf *params, t_map tile, int max);
void	delete_background_line_y(t_fdf *params, t_map tile, int max);
void	delete_background_center(t_fdf *params, t_map tile, int max);
void	delete_background(t_fdf *params, int y, int x);
void		draw_map_2d(t_fdf params);
t_mlx	init_struct_mlx(t_fdf *params);

// file

char		***parsing_line(char ***old_file, char *line);
char		***realloc_file(char ***old_file, int size);
char		***parsing_file(const char *name);

// map

t_map		**parsing_map(t_fdf *params);
t_map		fill_map(t_fdf *params, int y, int x);

// Tools 

void		rev_line(t_pos *line);
int			ft_tablen(char **tab);
int			ft_maplen(char ***map);
void		free_map_fdf(char ***map);
t_pos		search_max_line_fdf(char ***map);
int			check_error_fdf(char const *argv[]);
int			print_usage_fdf(const char *name, int error);

// draw

t_pos		*realloc_pos(t_pos *tab, t_pos pos, int size);
t_pos		*draw_line_vertical(char *mlx_img, t_draw info);
t_pos		*draw_line_horizontal(char *mlx_img, t_draw info);
t_pos		*draw_line(t_fdf params, t_map a, t_map b);

#endif