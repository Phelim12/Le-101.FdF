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


void	put_pixel_image(t_fdf *params, t_draw *info, int pix)
{
	char			*img;
	int				cur;

	img = (char *)params->mlx_img;
	if (info->a.y < 0 || info->a.x < 0 ||
		info->a.y >= info->s_win.y || info->a.x >= info->s_win.x)
		return ;
	cur = (4 * info->a.x) + (info->a.y * (info->s_win.x * 4));
	if (cur > (info->s_win.x * info->s_win.y * 4))
		return ;
	info->gradient.start[0] += info->gradient.inc[0];
	info->gradient.start[1] += info->gradient.inc[1];
	info->gradient.start[2] += info->gradient.inc[2];
	img[cur] = (char)((255 / 100) * info->gradient.start[0]);
	img[cur + 1] = (char)((255 / 100) * info->gradient.start[1]);
	img[cur + 2] = (char)((255 / 100) * info->gradient.start[2]);
	img[cur + 3] = 0;
}


t_pos	*draw_line_vertical(t_fdf *params, t_draw info, int cur)
{
	t_pos	*ret;

	info.count = (info.dis_y / 2);
	info.size = size_line_vertical(info);
	init_gradient_2(&info);
	put_pixel_image(params, &info, cur);
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
		put_pixel_image(params, &info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z || (info.a.z * info.alt) < 0)
		rev_line(ret);
	free(info.gradient.inc);
	free(info.gradient.start);
	return (ret);
}

t_pos	*draw_line_horizontal(t_fdf *params, t_draw info, int cur)
{
	t_pos	*ret;

	info.count = (info.dis_x / 2);
	info.size = size_line_horizontal(info);
	init_gradient_2(&info);
	put_pixel_image(params, &info, cur);
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
		put_pixel_image(params, &info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z || (info.a.z * info.alt) < 0)
		rev_line(ret);
	free(info.gradient.inc);
	free(info.gradient.start);
	return (ret);
}

t_pos	*draw_line(t_fdf *params, t_map a, t_map b)
{
	t_draw	info;

	info.a = a.coord;
	info.b = b.coord;
	info.col_a = a.color;
	info.col_b = b.color;
	info.alt = params->alt;
	info.s_win = params->s_win;
	info.dis_y = FT_ABS((info.a.y - info.b.y));
	info.dis_x = FT_ABS((info.a.x - info.b.x));
	info.xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	info.yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	info.gradient = init_gradient_1(info);
	if (info.dis_x > info.dis_y)
		return (draw_line_horizontal(params, info, 1));
	else
		return (draw_line_vertical(params, info, 1));
}

int 	check_print_line_x(t_fdf params, int y, int x)
{
	if (x < (params.s_map.x - 1))
	{
		if (((MAP[y][x].coord.x < 0) && (MAP[y][x + 1].coord.x < 0)) || 
			((MAP[y][x].coord.y < 0) && (MAP[y][x + 1].coord.y < 0)) ||
			((MAP[y][x].coord.x > params.s_win.x) && 
			(MAP[y][x + 1].coord.x > params.s_win.x)) ||
			((MAP[y][x].coord.y > params.s_win.y) && 
			(MAP[y][x + 1].coord.y > params.s_win.y)))
			return (0);
	}
	return (1);
}

int 	check_print_line_y(t_fdf params, int y, int x)
{
	if (y < (params.s_map.y - 1))
	{
		if (((MAP[y][x].coord.x < 0) && (MAP[y + 1][x].coord.x < 0)) || 
			((MAP[y][x].coord.y < 0) && (MAP[y + 1][x].coord.y < 0))||
			((MAP[y][x].coord.x > params.s_win.x) && 
			(MAP[y + 1][x].coord.x > params.s_win.x)) ||
			((MAP[y][x].coord.y > params.s_win.y) && 
			(MAP[y + 1][x].coord.y > params.s_win.y)))
			return (0);
	}
	return (1);
}

int 	faster_display_x(t_fdf params, int y, int x)
{
	int s_win_x;
	int s_win_y;

	s_win_x = params.s_win.x;
	s_win_y = params.s_win.y;
	if ((x + 1) < (params.s_map.x - 1))
	{
		if (((MAP[y][x].coord.x < 0) && (MAP[y][x + 1].coord.x < 0)) ||
			((MAP[y][x].coord.x > s_win_x) && (MAP[y][x + 1].coord.x > s_win_x)))
			return (0);
		if ((MAP[y][x].coord.y > s_win_y) && (MAP[y][x + 1].coord.y > s_win_y))
			return (0);
	}
	if ((x + 1) < (params.s_map.x - 1) && (y + 1) < (params.s_map.y - 1))
	{
		if (((MAP[y][x].coord.y < 0) && (MAP[y + 1][x].coord.y < 0)) &&
			MAP[y + 1][x + 1].coord.y < 0)
			return (0);
	}
	return (1);
}

int 	faster_display_y(t_fdf params, int y, int x)
{
	int s_win_x;
	int s_win_y;

	s_win_x = params.s_win.x;
	s_win_y = params.s_win.y;
	if ((y + 1) < (params.s_map.y - 1))
	{
		if (((MAP[y][x].coord.x < 0) && (MAP[y + 1][x].coord.x < 0)) ||
			((MAP[y][x].coord.x > s_win_x) && (MAP[y + 1][x].coord.x > s_win_x)))
			return (0);
		if ((MAP[y][x].coord.y > s_win_y) && (MAP[y + 1][x].coord.y > s_win_y))
			return (0);
	}
	if ((x + 1) < (params.s_map.x - 1) && (y + 1) < (params.s_map.y - 1))
	{
		if (((MAP[y][x].coord.y < 0) && (MAP[y][x + 1].coord.y < 0)) &&
			MAP[y + 1][x + 1].coord.y < 0)
			return (0);
	}
	return (1);
}

void	delete_first_line(t_fdf *params)
{
	char *img;
	int cur;
	int stop;

	cur = -1;
	img = params->mlx_img;
	stop = (params->s_win.x * 4);
	while (++cur < stop)
	{
		img[cur] = 0;
	}
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
			if (x < (params.s_map.x - 1) && faster_display_x(params, y, x))
				MAP[y][x].line_x = draw_line(&params, MAP[y][x], MAP[y][1 + x]);
			if (y < (params.s_map.y - 1) && faster_display_y(params, y, x))
				MAP[y][x].line_y = draw_line(&params, MAP[y][x], MAP[y + 1][x]);
			delete_background(&params, y, x);
		}
	}
	delete_first_line(&params);
}


