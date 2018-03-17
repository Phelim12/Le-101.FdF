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

t_map	fill_real_map(char *params, int size_line, t_pos size_window, t_pos cur, t_pos center)
{
	t_map ret;

	//if (ft_strchr(params, ','))d
	//	ret.color = hexa(ft_strchr(params, ','));
	ret.coord.z = ft_atoi(params);
	ret.coord.x = (center.x + ((cur.x - cur.y) * (size_line / 1.3)));
	ret.coord.y = (center.y + ((cur.x + cur.y) * (size_line / 3)) - (ret.coord.z * 5));
	//printf("alt = %d\t x = %d\t y = %d\t curx = %d\t cury = %d\t", ret.coord.z, ret.coord.x, ret.coord.y, cur.x, cur.y);
	ret.stop = 1;
	return (ret);
}

t_map	**parsing_real_map(char ***map, t_pos size_window)
{
	int		size_line;
	t_pos	size_map;
	t_pos	center;
	t_map	**ret;
	t_pos	cur;

	cur.y = -1;
	size_map = search_max_line_fdf(map);
	size_line = ((((size_window.x * 60) / 100) + ((size_window.y * 60) / 100))) / (size_map.y + size_map.x);
	center.x = (size_window.x / 2) + ((((size_map.y - 1) - (size_map.x - 1)) * (size_line / 1.3)) / 2);
	center.y = ((size_window.y - (((size_map.y - 1) + (size_map.x - 1)) * (size_line / 3))) / 2);
	ret = (t_map **)malloc(sizeof(t_map *) * (size_map.y + 2));
	while (map[++cur.y])
	{
		cur.x = -1;
		ret[cur.y] = (t_map *)malloc(sizeof(t_map) * (size_map.x + 2));
		while (map[cur.y][++cur.x])
			ret[cur.y][cur.x] = fill_real_map(map[cur.y][cur.x], size_line,\
			 size_window, cur, center);
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












