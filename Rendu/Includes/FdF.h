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
//#include "../Minilibx/mlx_int.h"
//#include "../Minilibx/mlx_new_window.h"

typedef struct	s_pos
{
	int	z;
	int	y;
	int x;
}				t_pos;

typedef struct	s_draw
{
	t_pos a;
	t_pos b;
	int count;
	int dis_x;
	int dis_y;
}				t_draw;

typedef struct	s_map
{
	t_pos	coord;
	int		color;
	int		stop;
}				t_map;

int		ft_tablen(char **tab);
char	***realloc_map(char ***old_map, int size);
char	***parsing_line(char ***old_map, char *line);
t_map	**parsing_map(const char *name, t_pos size_window);

void		draw_line_vertical(void *mlx_ptr, void *win_ptr, t_draw info);
void		draw_line_horizontal(void *mlx_ptr, void *win_ptr, t_draw info);
void		draw_line(void *mlx_ptr, void *win_ptr, t_pos a, t_pos b);

#endif