/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_fdf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/14 19:28:18 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/14 19:28:18 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

int		ft_tablen(char **tab)
{
	int	ret;

	ret = -1;
	while (tab[++ret])
		;
	return (ret + 2);
}

int		ft_maplen(char ***map)
{
	int	ret;

	ret = -1;
	while (map[++ret])
		;
	return (ret + 2);
}

void	free_map_fdf(char ***map)
{
	int x;
	int y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			free(map[y][x]);
		free(map[y]);
	}
	free(map);
}

void	rev_line(t_pos *line)
{
	t_pos	swap;
	int		start;
	int		end;

	end = 0;
	start = 0;
	while (line[end].y != - 1)
		end++;
	end--;
	while (end > start)
	{
		swap = line[end];
		line[end] = line[start];
		line[start] = swap;
		start++;
		end--;
	}
}

t_pos	search_max_line_fdf(char ***map)
{
	t_pos ret;
	int y;
	int x;

	y = -1;
	ret.x = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			;
		if (x > ret.x)
			ret.x = x;
	}
	ret.y = y;
	return (ret);
}
