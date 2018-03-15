/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prasing_fdf.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/14 16:07:05 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/14 16:07:05 by clcreuso    ###    #+. /#+    ###.fr     */
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

int		ft_mapline(char ***map)
{
	int	ret;

	ret = -1;
	while (map[++ret])
		;
	return (ret + 2);
}

void		free_map_fdf(char ***map)
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

char	***realloc_map(char ***old_map, int size)
{
	char	***new_map;
	int		y;
	int		x;

	y = -1;
	new_map = (char ***)malloc(sizeof(char **) * (size + 2));
	while (old_map[++y])
	{
		x = -1;
		new_map[y] = (char **)malloc(sizeof(char *) * (ft_tablen(old_map[y])));
		while (old_map[y][++x])
		{
			new_map[y][x + 1] = NULL;
			new_map[y][x] = ft_strdup(old_map[y][x]);
			free(old_map[y][x]);
		}
		free(old_map[y]);
	}
	free(old_map);
	return (new_map);
}

char	***parsing_line(char ***old_map, char *line)
{
	char		***new_map;
	int static	cur = 0;

	if (old_map)
		new_map = realloc_map(old_map, cur);
	else
		new_map = (char ***)malloc(sizeof(char **) * (cur + 2));
	new_map[cur++] = ft_strsplit(line, ' ');
	new_map[cur] = NULL;
	return (new_map);
}

t_pos		search_max_line_fdf(char ***map)
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

t_map	fill_real_map(char *params, int size_line, t_pos size_window, t_pos cur)
{
	t_map ret;
	int static test = 0;

	//if (ft_strchr(params, ','))
	//	ret.color = hexa(ft_strchr(params, ','));
	ret.coord.z = ft_atoi(params);
	ret.coord.x = (size_window.x / 2) + ((cur.x - cur.y) * (size_line / 2));
	ret.coord.y = ((cur.x + cur.y) * (size_line / 2)) - ret.coord.z * 5.5;
	ret.stop = 1;
	return (ret);
}

t_map	**parsing_real_map(char ***map, t_pos size_window)
{
	int		size_line;
	t_pos	size_map;
	t_map	**ret;
	t_pos	cur;

	cur.y = -1;
	size_map = search_max_line_fdf(map);
	size_line = (((size_window.x * 50) / 100) + ((size_window.y * 50) / 100));
	size_line /= (size_map.y + size_map.x);
	ret = (t_map **)malloc(sizeof(t_map *) * (ft_mapline(map)));
	while (map[++cur.y])
	{
		cur.x = -1;
		ret[cur.y] = (t_map *)malloc(sizeof(t_map) * (ft_tablen(map[cur.y])));
		while (map[cur.y][++cur.x])
			ret[cur.y][cur.x] = fill_real_map(map[cur.y][cur.x], size_line,\
			 size_window, cur);
		ret[cur.y][cur.x].stop = 0;
	}
	ret[cur.y] = NULL;
	return (ret);
}

t_map	**parsing_map(const char *name, t_pos size_window)
{
	char	***map;
	t_map	**ret;
	char	*line;
	int 	fd;

	map = NULL;
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		map = parsing_line(map, line);
		free(line);
	}
	ret = parsing_real_map(map, size_window);
	return (ret);
}













