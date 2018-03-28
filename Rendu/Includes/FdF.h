/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
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
# define MAP_YX (MAP[y][x])
# define S_L (&(params->s_l))
# define BPP (&(params->bpp))
# define MAP_PX (MAP[y][x + 1])
# define MAP_PY (MAP[y + 1][x])
# define MAP_PTR (params->map)
# define WIN_PTR (params.win_ptr)
# define IMG_PTR (params->img_ptr)
# define MLX_PTR (params->mlx_ptr)
# define ENDIAN (&(params->endian))

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../Minilibx/mlx.h"
# include "../Libft/Includes/libft.h"

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃     This structure groups position x (width), y (height), z (altitude).    ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct	s_pos
{
	int	z;
	int	y;
	int x;
}				t_pos;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃      This structure groups the parameters for each point of the map.       ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct	s_map
{
	t_pos	*line_y;
	t_pos	*line_x;
	t_pos	coord;
	int		color;
	int		stop;
}				t_map;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃            This structure groups the display function variables            ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct	s_draw
{
	t_pos	s_win;
	t_pos	a;
	t_pos	b;
	int		z;
	int		xinc;
	int		yinc;
	int		size;
	int		count;
	int		col_a;
	int		col_b;
	int		dis_x;
	int		dis_y;
	float	*start;
	float	*inc;
	float	alt;
}				t_draw;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                This structure groups the principal variables               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct	s_fdf
{
	char	***file_map;
	t_map	**map;
	t_pos	center;
	t_pos	s_win;
	t_pos	s_map;
	void	*mlx_img;
	void	*win_ptr;
	void	*img_ptr;
	void	*mlx_ptr;
	float	alt;
	int		s_line;
	int		endian;
	int		min_y;
	int		bpp;
	int		s_l;
	int		y;
	int		x;
}				t_fdf;

#endif
