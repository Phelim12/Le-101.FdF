/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 20:44:20 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/13 20:44:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

int		nb_pixel_line_vertical(t_draw info)
{
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_y / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	while (cur++ <= info.dis_y)
	{
		info.a.y += yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += xinc;
		}
	}
	return (cur);
}

int		nb_pixel_line_horizontal(t_draw info)
{
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_x / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	while (cur++ <= info.dis_x)
	{
		info.a.x += xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += yinc;
		}
	}
	return (cur);
}

int		nb_pixel_line(t_pos a, t_pos b)
{
	t_draw	info;

	info.a = a;
	info.b = b;
	info.dis_y = FT_ABS((a.y - b.y));
	info.dis_x = FT_ABS((a.x - b.x));
	if (info.dis_x > info.dis_y)
		return (nb_pixel_line_horizontal(info));
	else
		return (nb_pixel_line_vertical(info));
}

void		draw_line_vertical(void *mlx_ptr, void *win_ptr, t_draw info)
{
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_y / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	mlx_pixel_put(mlx_ptr, win_ptr, info.a.x, info.a.y, 0xfffafa);
	while (cur++ <= info.dis_y)
	{
		info.a.y += yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += xinc;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, info.a.x, info.a.y, 0xfffafa);
	}
}

void		draw_line_horizontal(void *mlx_ptr, void *win_ptr, t_draw info)
{
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_x / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	mlx_pixel_put(mlx_ptr, win_ptr, info.a.x, info.a.y, 0xfffafa);
	while (cur++ <= info.dis_x)
	{
		info.a.x += xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += yinc;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, info.a.x, info.a.y, 0xfffafa);
	}
}

void		draw_line(void *mlx_ptr, void *win_ptr, t_pos a, t_pos b)
{
	t_draw	info;

	info.a = a;
	info.b = b;
	info.dis_y = FT_ABS((a.y - b.y));
	info.dis_x = FT_ABS((a.x - b.x));
	if (info.dis_x > info.dis_y)
		draw_line_horizontal(mlx_ptr, win_ptr, info);
	else
		draw_line_vertical(mlx_ptr, win_ptr, info);
}

