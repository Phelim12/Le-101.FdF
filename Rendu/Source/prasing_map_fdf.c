/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prasing_map_fdf.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/19 16:38:07 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/19 16:38:07 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"


int		ft_hexatoi(const char *s)
{
	int nb;

	nb = 0;
	while (*s == 32)
		s++;
	if (*s == '0' && s++)
		if (*s++ != 'x')
			return (0);
	while ((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F')
		|| (*s >= 'a' && *s <= 'f'))
	{
		if (*s >= '0' && *s <= '9')
			nb = nb * 16 + (*s++ - '0');
		else if (*s >= 'a' && *s <= 'f')
			nb = nb * 16 + (*s++ - 'W');
		else
			nb = nb * 16 + (*s++ - '7');
	}
	return (nb);
}

void	init_struct_fdf(t_fdf *ptr)
{
	float	zoom;
	float	alt;
	int		c_x;
	int 	c_y;

	zoom = 1.5;
	alt = 1;
	alt += zoom;
	ptr->s_map = search_max_line_fdf(ptr->file_map);
	ptr->s_line = (ptr->s_win.x + ptr->s_win.y);
	ptr->s_line /= ((ptr->s_map.y + ptr->s_map.x) / zoom);
	if (ptr->s_line < 3)
		ptr->s_line = 3;
	c_x = ((ptr->s_map.x - 1) - (ptr->s_map.y - 1)) * (ptr->s_line / 1.3);
	c_y = ((ptr->s_map.x - 1) + (ptr->s_map.y - 1)) * (ptr->s_line / 3);
	ptr->center.x = (ptr->s_win.x / 2) - (c_x / 2);
	ptr->center.y = (ptr->s_win.y / 2) - (c_y / 2);
	ptr->center.y += (ptr->s_map.z * alt);
}

t_map	fill_map(t_fdf *params, int y, int x)
{
	float	zoom;
	float	alt;
	t_map	ret;

	zoom = 1.5;
	alt = 1;
	alt += zoom;
	ret.coord.z = ft_atoi(params->file_map[y][x]);
	ret.coord.x = (params->center.x + ((x - y) * (params->s_line / 1.3)));
	ret.coord.y = (params->center.y + ((x + y) * (params->s_line / 3)));
	ret.coord.y -= (ret.coord.z * alt);
	if (ft_strstr(params->file_map[y][x], "0x"))
		ret.color = ft_hexatoi(ft_strstr(params->file_map[y][x], "0x") + 2);
	else
		ret.color = 16777215;
	ret.stop = 1;
	return (ret);
}

t_map	**parsing_map(t_fdf *params)
{
	t_map	**ret;
	int		y;
	int		x;

	y = -1;
	init_struct_fdf(params);
	ret = (t_map **)malloc(sizeof(t_map *) * (params->s_map.y + 2));
	while (params->file_map[++y])
	{
		x = -1;
		ret[y] = (t_map *)malloc(sizeof(t_map) * (params->s_map.x + 2));
		while (params->file_map[y][++x])
			ret[y][x] = fill_map(params, y, x);
		ret[y][x].stop = 0;
	}
	ret[y] = NULL;
	return (ret);
}

