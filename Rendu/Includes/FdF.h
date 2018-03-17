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
	t_pos size_window;
	t_pos a;
	t_pos b;
	int count;
	int dis_x;
	int dis_y;
	int	xinc;
	int	yinc;
}				t_draw;

typedef struct	s_map
{
	t_pos	*line_y;
	t_pos	*line_x;
	t_pos	coord;
	int		color;
	int		stop;
}				t_map;

typedef struct	s_mlx
{
	void	*win_ptr;
	void	*img_ptr;
	void	*mlx_ptr;
	void	*mlx_img;
	int		endian;
	int 	bpp;
	int		s_l;
}				t_mlx;

int		ft_tablen(char **tab);
char	***realloc_map(char ***old_map, int size);
char	***parsing_line(char ***old_map, char *line);
t_map	**parsing_map(const char *name, t_pos size_window);
t_pos	fill_pos(int y, int x);
t_pos	*draw_line(char *mlx_img, t_pos a, t_pos b, t_pos size_window);
void	put_pixel_image(char *mlx_img, t_pos print, t_pos size_window);
int		nb_pixel_line(t_pos a, t_pos b);
int		ft_tablen(char **tab);
int		ft_maplen(char ***map);
void	free_map_fdf(char ***map);
void	rev_line(t_pos *line);
t_pos	search_max_line_fdf(char ***map);

#endif