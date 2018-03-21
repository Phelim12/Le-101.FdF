/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_fdf.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 19:41:40 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 19:41:40 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"


void	put_pixel_black(t_fdf *params, t_pos print)
{
	int 			black;
	char			*img;
	int				cur;

	black = 0;
	img = (char *)params->mlx_img;
	if (print.y < 0 || print.x < 0 || print.y >= params->s_win.y || print.x >= params->s_win.x)
		return ;
	cur = (4 * print.x) + (print.y * (params->s_win.x * 4));
	if (cur > (params->s_win.x * params->s_win.y * 4))
		return ;
	ft_memcpy(img + cur, &black, 4);
}

t_pos	*draw_line_vertical(char *mlx_img, t_draw info)
{
	t_pos	*ret;
	int		cur;

	cur = 1;
	info.count = (info.dis_y / 2);
	info.size = size_line_vertical(info);
	init_gradient_2(&info);
	put_pixel_image(mlx_img, &info, cur);
	ret = (t_pos*)malloc(sizeof(t_pos) * (info.size + 2));
	while (cur++ <= info.dis_y)
	{
		info.a.y += info.yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += info.xinc;
		}
		put_pixel_image(mlx_img, &info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if ((info.a.z == info.z) && ((info.a.z * info.alt) < (info.b.z * info.alt)))
		rev_line(ret);
	return (ret);
}

t_pos	*draw_line_horizontal(char *mlx_img, t_draw info)
{
	t_pos	*ret;
	int		cur;

	cur = 1;
	info.count = (info.dis_x / 2);
	info.size = size_line_horizontal(info);
	init_gradient_2(&info);
	put_pixel_image(mlx_img, &info, cur);
	ret = (t_pos*)malloc(sizeof(t_pos) * (info.size + 2));
	while (cur++ <= info.dis_x)
	{
		info.a.x += info.xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += info.yinc;
		}
		put_pixel_image(mlx_img, &info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if ((info.a.z == info.z) && ((info.a.z * info.alt) < (info.b.z * info.alt)))
		rev_line(ret);
	return (ret);
}

t_pos	*draw_line(t_fdf params, t_map a, t_map b)
{
	t_draw	info;

	info.a = a.coord;
	info.b = b.coord;
	info.col_a = a.color;
	info.col_b = b.color;
	info.s_win = params.s_win;
	info.dis_y = FT_ABS((info.a.y - info.b.y));
	info.dis_x = FT_ABS((info.a.x - info.b.x));
	info.xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	info.yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	info.gradient = init_gradient_1(info);
	info.alt = params.alt;
	if ((params.cur.y < (params.s_map.x - 1)) && (params.cur.y < (params.s_map.y - 1)))
		info.z = MAP[params.cur.y + 1][params.cur.x + 1].coord.z;
	if (info.dis_x > info.dis_y)
		return (draw_line_horizontal(params.mlx_img, info));
	else
		return (draw_line_vertical(params.mlx_img, info));
}

void	draw_map_2d(t_fdf params)
{
	int		y;
	int		x;

	y = -1;
	while (MAP[++y])
	{
		x = -1;
		while (MAP[y][++x].stop)
		{	
			MAP[y][x].line_x = NULL;
			MAP[y][x].line_y = NULL;
			params.cur = fill_pos(y, x);
			if (x < (params.s_map.x - 1))
				MAP[y][x].line_x = draw_line(params, MAP[y][x], MAP[y][1 + x]);
			if (y < (params.s_map.y - 1))
				MAP[y][x].line_y = draw_line(params, MAP[y][x], MAP[y + 1][x]);
			delete_background(&params, y, x);
		}
	}
}
