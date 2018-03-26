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

#include "fdf.h"
#include "function_fdf.h"

void	put_pixel_black(t_fdf *params, t_pos print)
{
	int		black;
	char	*img;
	int		cur;

	black = 0;
	img = (char *)params->mlx_img;
	if (print.y < 0 || print.x < 0 || print.y >= params->s_win.y ||
		print.x >= params->s_win.x)
		return ;
	cur = (4 * print.x) + (print.y * (params->s_win.x * 4));
	if (cur > (params->s_win.x * params->s_win.y * 4))
		return ;
	ft_memcpy(img + cur, &black, 4);
}

void	put_pixel_image(t_fdf *params, t_draw *info)
{
	unsigned char	*img;
	int				cur;

	img = (unsigned char *)params->mlx_img;
	if (info->a.y < 0 || info->a.x < 0 || info->a.y >= info->s_win.y ||
		info->a.x >= info->s_win.x)
		return ;
	cur = (4 * info->a.x) + (info->a.y * (info->s_win.x * 4));
	if (cur > (info->s_win.x * info->s_win.y * 4))
		return ;
	img[cur] = (unsigned char)(((float)255 / (float)100) * info->start[0]);
	img[cur + 1] = (unsigned char)(((float)255 / (float)100) * info->start[1]);
	img[cur + 2] = (unsigned char)(((float)255 / (float)100) * info->start[2]);
	info->start[0] += info->inc[0];
	info->start[1] += info->inc[1];
	info->start[2] += info->inc[2];
	img[cur + 3] = 0;
}

t_pos	*draw_line_vertical(t_fdf *params, t_draw info, int cur)
{
	t_pos	*ret;

	info.count = (info.dis_y / 2);
	info.size = size_line_vertical(info);
	init_gradient_2(&info);
	put_pixel_image(params, &info);
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
		put_pixel_image(params, &info);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z || (info.a.z * info.alt) < 0)
		rev_line(ret);
	free(info.inc);
	free(info.start);
	return (ret);
}

t_pos	*draw_line_horizontal(t_fdf *params, t_draw info, int cur)
{
	t_pos	*ret;

	info.count = (info.dis_x / 2);
	info.size = size_line_horizontal(info);
	init_gradient_2(&info);
	put_pixel_image(params, &info);
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
		put_pixel_image(params, &info);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z || (info.a.z * info.alt) < 0)
		rev_line(ret);
	free(info.inc);
	free(info.start);
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
	init_gradient_1(&info);
	if (info.dis_x > info.dis_y)
		return (draw_line_horizontal(params, info, 1));
	else
		return (draw_line_vertical(params, info, 1));
}
