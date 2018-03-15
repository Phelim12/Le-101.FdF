/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_fdf.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/12 19:22:32 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/12 19:22:32 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

t_pos	fill_pos(int y, int x)
{
	t_pos ret;

	ret.y = y;
	ret.x = x;
	return (ret);
}


void	draw_map_2d(void *mlx_ptr, void *win_ptr, t_map **map)
{
	int		y;
	int		x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x].stop)
		{
			if (map[y][1 + x].stop)
				draw_line(mlx_ptr, win_ptr, map[y][x].coord, map[y][1 + x].coord);
			if (map[1 + y])
				draw_line(mlx_ptr, win_ptr, map[y][x].coord, map[y + 1][x].coord);
		}
	}
}

int		main(int argc, char const *argv[])
{
	t_pos	size_window;
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	**map;
	
	size_window.y = 1000;
	size_window.x = 1000;
	if (argv[1])
		map = parsing_map(argv[1], size_window);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FdF");
	draw_map_2d(mlx_ptr, win_ptr, map);
	mlx_loop(mlx_ptr);
	return (0);
} 

