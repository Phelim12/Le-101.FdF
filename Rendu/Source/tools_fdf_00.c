/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_fdf_00.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/26 18:59:57 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/26 18:59:57 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

void	free_map_fdf(t_fdf *params)
{
	int		y;

	y = -1;
	while (params->map[++y])
	{
		free(params->map[y]);
	}
	free(params->map);
}

void	free_file_fdf(char ***map)
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
	while (line[end].y != -1)
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

int		modif_params_map(int key, t_fdf *params)
{
	if (key == 69)
		params->s_line += 1;
	if (key == 78)
		params->s_line -= 1;
	if (key == 24)
		params->alt += 0.1;
	if (key == 27)
		params->alt -= 0.1;
	if (key == 125)
		params->y -= (params->s_win.y / 20);
	if (key == 126)
		params->y += (params->s_win.y / 20);
	if (key == 123)
		params->x += (params->s_win.x / 20);
	if (key == 124)
		params->x -= (params->s_win.x / 20);
	if (params->s_line < 3)
	{
		params->s_line = 3;
		return (1);
	}
	return (0);
}
