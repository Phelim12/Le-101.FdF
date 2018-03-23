/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_draw_fdf.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 19:41:35 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 19:41:35 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

int		size_line_vertical(t_draw info)
{
	int		ret;

	ret = 1;
	info.count = (info.dis_y / 2);
	while (ret++ <= info.dis_y)
	{
		info.a.y += info.yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += info.xinc;
		}
	}
	return (ret);
}

int		size_line_horizontal(t_draw info)
{
	int		ret;

	ret = 1;
	info.count = (info.dis_x / 2);
	while (ret++ <= info.dis_x)
	{
		info.a.x += info.xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += info.yinc;
		}
	}
	return (ret);
}

void	init_gradient_2(t_draw *info)
{
	info->gradient.inc[0] = -((info->gradient.inc[0] * 90) / info->size);
	info->gradient.inc[1] = -((info->gradient.inc[1] * 90) / info->size);
	info->gradient.inc[2] = -((info->gradient.inc[2] * 90) / info->size);
}

t_test	init_gradient_1(t_draw info)
{
	unsigned char	*col_a;
	unsigned char	*col_b;
	t_test			gradient;

	col_a = (unsigned char *)ft_strnew(5);
	col_b = (unsigned char *)ft_strnew(5);
	gradient.inc = (float *)malloc(sizeof(float) * (4));
	gradient.start = (float *)malloc(sizeof(float) * (4));
	ft_memcpy(col_a, &info.col_a, 4);
	ft_memcpy(col_b, &info.col_b, 4);
	gradient.start[0] = (float)(((float)col_a[0] / 255) * 100);
	gradient.start[1] = (float)(((float)col_a[1] / 255) * 100);
	gradient.start[2] = (float)(((float)col_a[2] / 255) * 100);
	gradient.inc[0] = (col_a[0] == col_b[0]) ? 0 : \
	(float)(FT_ABS(col_a[0] - col_b[0]) / (float)255);
	gradient.inc[1] = (col_a[1] == col_b[1]) ? 0 : \
	(float)(FT_ABS(col_a[1] - col_b[1]) / (float)255);
	gradient.inc[2] = (col_a[2] == col_b[2]) ? 0 : \
	(float)(FT_ABS(col_a[2] - col_b[2]) / (float)255);
	free(col_a);
	free(col_b);
	return (gradient);
}