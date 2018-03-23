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

t_pos	fill_pos(int y, int x)
{
	t_pos ret;

	ret.y = y;
	ret.x = x;
	return (ret);
}

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

int		check_error_fdf(char const *argv[])
{
	int fd;

	if (!(argv[1]) || argv[2])
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (2);
	close(fd);
	return (0);
}

int		print_usage_fdf(const char *name, int error)
{
	if (error == 1)
		ft_putendl_fd("usage: fdf [file]", 1);
	if (error == 2)
	{
		ft_putstr_fd("fdf: no such file or directory: ", 2);
		ft_putendl_fd(name, 2);
	}
	return (0);
}

int		search_floor_map(t_pos relief, int *tab)
{
	int		s_cur;
	int		max;
	int		cur;

	max = 0;
	cur = -1;
	while (++cur < relief.y + FT_ABS(relief.x))
	{
		if (tab[cur] > max)
		{
			max = tab[cur];
			s_cur = cur;
		}
	}
	return (s_cur - relief.x);
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
	tab = (int *)ft_memalloc(sizeof(int) * (relief.y + FT_ABS(relief.x) + 10));
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			tab[ft_atoi(map[y][x]) + FT_ABS(relief.x)]++;
		if (x > ret.x)
			ret.x = x;
	}
	ret.z = search_floor_map(relief, tab);
	free(tab);
	ret.y = y;
	return (ret);
}