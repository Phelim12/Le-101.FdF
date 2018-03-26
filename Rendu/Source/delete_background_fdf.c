/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_background_fdf.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 16:31:18 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/20 16:31:18 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

int		check_delete(t_pos *line, int y, int x)
{
	int cur;

	cur = 0;
	if (!(line))
		return (0);
	while (line[cur].x != -1 || line[cur].y != -1)
	{
		if (line[cur].x == x && line[cur].y == y)
			return (1);
		cur++;
	}
	return (0);
}

void	delete_background_line_x(t_fdf *params, t_map tile, int max, int inc)
{
	int cur1;
	int cur2;

	cur1 = (inc < 0) ? 1 : 0;
	inc = (inc < 0) ? -1 : 1;
	while (tile.line_x[cur1].x != -1 || tile.line_x[cur1].y != -1)
	{
		cur2 = (tile.line_x[cur1].y > 0) ? tile.line_x[cur1].y : 0;
		while (tile.line_x[cur1].x != tile.line_x[cur1 + inc].x && cur2 < max)
			put_pixel_black(params, fill_pos(++cur2, tile.line_x[cur1].x));
		cur1++;
	}
}

void	delete_background_line_y(t_fdf *params, t_map tile, int max, int inc)
{
	int cur1;
	int cur2;

	cur1 = (inc < 0) ? 1 : 0;
	inc = (inc < 0) ? -1 : 1;
	while (tile.line_y[cur1].x != -1 || tile.line_y[cur1].y != -1)
	{
		cur2 = (tile.line_y[cur1].y > 0) ? tile.line_y[cur1].y : 0;
		while (tile.line_y[cur1].x != tile.line_y[cur1 + inc].x && cur2 < max)
			put_pixel_black(params, fill_pos(++cur2, tile.line_y[cur1].x));
		cur1++;
	}
}

void	delete_background_center(t_fdf *params, int y, int x, int max)
{
	t_pos	*line_y;
	t_pos	*line_x;
	int		s_x;
	int		cur;

	line_y = NULL;
	line_x = NULL;
	if (MAP_PTR[y][x].line_y)
		line_y = MAP_PTR[y][x].line_y;
	if (MAP_PTR[y][x].line_x)
		line_x = MAP_PTR[y][x].line_x;
	s_x = MAP_PTR[y][x].coord.x;
	cur = (MAP_PTR[y][x].coord.y > -1) ? (MAP_PTR[y][x].coord.y + 1) : 0;
	while (check_delete(line_x, cur, s_x) || check_delete(line_y, cur, s_x))
		cur++;
	while (cur < max)
		put_pixel_black(params, fill_pos(cur++, s_x));
}

void	delete_background(t_fdf *params, int y, int x)
{
	t_map	tile;
	int		inc;
	int		max;

	max = 0;
	tile = MAP_PTR[y][x];
	if (tile.line_x && tile.line_y)
		max = (MAP_PTR[y + 1][x + 1].coord.y);
	else if (tile.line_y && tile.line_x && max < MAP_PTR[y + 1][x].coord.y)
		max = (MAP_PTR[y + 1][x].coord.y);
	else if (tile.line_y && tile.line_x && max < MAP_PTR[y][x + 1].coord.y)
		max = (MAP_PTR[y][x + 1].coord.y);
	else
		max = params->s_win.y;
	delete_background_center(params, y, x, max);
	if (tile.line_x)
	{
		inc = ((MAP_PTR[y][x + 1].coord.z) * params->alt);
		delete_background_line_x(params, tile, max, inc);
	}
	if (tile.line_y)
	{
		inc = ((MAP_PTR[y + 1][x].coord.z) * params->alt);
		delete_background_line_y(params, tile, max, inc);
	}
}
