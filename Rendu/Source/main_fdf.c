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

void	put_pixel_image(char *mlx_img, t_pos print, t_pos sw)
{
	int count;

	if (print.y < 0 || print.x < 0 || print.y >= sw.y || print.x >= sw.x)
		return ;
	count = (4 * print.x) + (print.y * (sw.y * 4));
	if (count > (sw.x * sw.y * 4))
		return ;
	mlx_img[count] = -1;
	mlx_img[count + 1] = -1;
	mlx_img[count + 2] = -1;
	mlx_img[count + 3] = 0;
}

void	put_pixel_black(char *mlx_img, t_pos print, t_pos sw)
{
	int count;

	if (print.y < 0 || print.x < 0 || print.y >= sw.y || print.x >= sw.x)
		return ;
	count = (4 * print.x) + (print.y * (sw.y * 4));
	if (count > (sw.x * sw.y * 4))
		return ;
	mlx_img[count] = 0;
	mlx_img[count + 1] = 0;
	mlx_img[count + 2] = 0;
	mlx_img[count + 3] = 0;
}

void	delete_background_line_x(char *mlx_img, t_map tile, t_pos size_window, int max)
{
	int cur1;
	int cur2;

	cur1 = 0;
	while (tile.line_x[cur1].x != -1 || tile.line_x[cur1].y != -1)
	{
		cur2 = tile.line_x[cur1].y;
		while (tile.line_x[cur1].x != tile.line_x[cur1 + 1].x && cur2 < max + 10)
			put_pixel_black(mlx_img, fill_pos(++cur2, tile.line_x[cur1].x), size_window);
		cur1++;
	}
}

void	delete_background_line_y(char *mlx_img, t_map tile, t_pos size_window, int max)
{
	int cur1;
	int cur2;

	cur1 = 0;
	while (tile.line_y[cur1].x != -1 || tile.line_y[cur1].y != -1)
	{
		cur2 = tile.line_y[cur1].y;
		while (tile.line_y[cur1].x != tile.line_y[cur1 + 1].x && cur2 < max + 10)
			put_pixel_black(mlx_img, fill_pos(++cur2, tile.line_y[cur1].x), size_window);
		cur1++;
	}
}

void	delete_background(char *mlx_img, t_map **map, t_pos size_window, t_pos pos)
{
	t_map	tile;
	int		max;
	int		cur;

	cur = 0;
	tile = map[pos.y][pos.x];
	if (tile.line_x && tile.line_y)
		max = map[pos.y + 1][pos.x + 1].coord.y;
	else
		max = size_window.y;
	while ((tile.line_x && tile.coord.x == tile.line_x[cur].x) ||
	 		(tile.line_y && tile.coord.x == tile.line_y[cur].x))
		cur++;
	cur += tile.coord.y;
	while (cur++ < max)
		put_pixel_black(mlx_img, fill_pos(cur, tile.coord.x), size_window);
	if (tile.line_x)
		delete_background_line_x(mlx_img, tile, size_window, max);
	if (tile.line_y)
		delete_background_line_y(mlx_img, tile, size_window, max);
}

void	draw_map_2d(char *mlx_img, t_map **map, t_pos size_window)
{
	int		y;
	int		x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x].stop)
		{
			map[y][x].line_x = NULL;
			map[y][x].line_y = NULL;
			if (map[y][1 + x].stop)
				map[y][x].line_x = draw_line(mlx_img, map[y][x].coord, map[y][1 + x].coord, size_window);
			if (map[1 + y])
				map[y][x].line_y = draw_line(mlx_img, map[y][x].coord, map[y + 1][x].coord, size_window);
			if (map[y][x].line_x && map[y][x].coord.z < map[y][x + 1].coord.z)
				rev_line(map[y][x].line_x);
			if (map[y][x].line_y && map[y][x].coord.z < map[y + 1][x].coord.z)
				rev_line(map[y][x].line_y);
			delete_background(mlx_img, map, size_window, fill_pos(y, x));
		}
	}
}

t_mlx	init_struct_mlx(t_pos sw)
{
	t_mlx	ret;

	ret.mlx_ptr = mlx_init();
	ret.win_ptr = mlx_new_window(ret.mlx_ptr, sw.x, sw.y, "FdF");
	ret.img_ptr = mlx_new_image(ret.mlx_ptr, sw.x, sw.y);
	ret.mlx_img = mlx_get_data_addr(ret.img_ptr, &(ret.bpp), &(ret.s_l), &(ret.endian));
	return (ret);
}

int		main(int argc, char const *argv[])
{
	t_pos	size_window;
	t_mlx	struct_mlx;
	t_map	**map;
	
	size_window.y = 1800;
	size_window.x = 1800;
	if (argv[1])
		map = parsing_map(argv[1], size_window);
	struct_mlx = init_struct_mlx(size_window);
	draw_map_2d(struct_mlx.mlx_img, map, size_window);
	put_pixel_black(struct_mlx.mlx_img, fill_pos(1001, 1001), size_window);
	mlx_put_image_to_window(struct_mlx.mlx_ptr, struct_mlx.win_ptr, struct_mlx.img_ptr, 0, 0);
	mlx_loop(struct_mlx.mlx_ptr);
	return (0);
} 

