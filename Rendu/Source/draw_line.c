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

t_pos	*realloc_pos(t_pos *tab, t_pos pos, int size)
{
	t_pos *ret;
	int cur;

	cur = -1;
	ret = (t_pos*)malloc(sizeof(t_pos) * (size));
	while (++cur < size - 2)
		ret[cur] = tab[cur];
	ret[cur] = pos;
	ret[cur + 1] = fill_pos(-1, -1);
	if (size > 2)
		free(tab);
	return (ret);
}

t_pos	*draw_line_vertical(char *mlx_img, t_draw info)
{
	t_pos *ret;
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_y / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	put_pixel_image(mlx_img, info.a, info.size_window);
	while (cur++ <= info.dis_y)
	{
		info.a.y += yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += xinc;
		}
		put_pixel_image(mlx_img, info.a, info.size_window);
		ret = realloc_pos(ret, info.a, cur);
	}
	return (ret);
}

t_pos	*draw_line_horizontal(char *mlx_img, t_draw info)
{
	t_pos *ret;
	int xinc;
	int yinc;
	int cur;

	cur = 1;
	info.count = (info.dis_x / 2);
	xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	put_pixel_image(mlx_img, info.a, info.size_window);
	while (cur++ <= info.dis_x)
	{
		info.a.x += xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += yinc;
		}
		put_pixel_image(mlx_img, info.a, info.size_window);
		ret = realloc_pos(ret, info.a, cur);
	}
	return (ret);
}

t_pos	*draw_line(char *mlx_img, t_pos a, t_pos b, t_pos size_window)
{
	t_draw	info;

	info.a = a;
	info.b = b;
	info.size_window = size_window;
	info.dis_y = FT_ABS((a.y - b.y));
	info.dis_x = FT_ABS((a.x - b.x));
	if (info.dis_x > info.dis_y)
		return (draw_line_horizontal(mlx_img, info));
	else
		return (draw_line_vertical(mlx_img, info));
}

