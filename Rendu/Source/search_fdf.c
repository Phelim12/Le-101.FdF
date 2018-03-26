/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_fdf.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 18:04:30 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/24 18:04:30 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

int		search_floor_map(t_pos relief, int *tab)
{
	int		s_cur;
	int		max;
	int		cur;

	max = 0;
	cur = -1;
	if (relief.y == 0 && relief.x == 0)
		return (0);
	while (++cur < relief.y + FT_ABS(relief.x))
	{
		if (tab[cur] > max)
		{
			max = tab[cur];
			s_cur = cur;
		}
	}
	return (s_cur);
}

t_pos	search_peak_and_crater(char ***map)
{
	t_pos	ret;
	int		y;
	int		x;

	y = -1;
	ret = fill_pos(0, 0);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_atoi(map[y][x]) < 0 && ft_atoi(map[y][x]) < ret.x)
				ret.x = ft_atoi(map[y][x]);
			if (ft_atoi(map[y][x]) >= 0 && ft_atoi(map[y][x]) > ret.y)
				ret.y = ft_atoi(map[y][x]);
		}
	}
	return (ret);
}

t_pos	search_max_line_fdf(char ***map)
{
	t_pos	relief;
	t_pos	ret;
	int		*tab;
	int		y;
	int		x;

	y = -1;
	ret.x = 0;
	relief = search_peak_and_crater(map);
	tab = (int *)ft_memalloc(sizeof(int) * (relief.y + FT_ABS(relief.x) + 9));
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			tab[ft_atoi(map[y][x]) + FT_ABS(relief.x)]++;
		if (x > ret.x)
			ret.x = x;
	}
	ret.z = search_floor_map(relief, tab);
	ret.y = y;
	free(tab);
	return (ret);
}
