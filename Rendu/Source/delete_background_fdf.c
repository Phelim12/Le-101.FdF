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

	cur = 1;
	if (!(line))
		return (0);
	while (cur <= line[cur].y)
	{
		if (line[cur].x == x && line[cur].y == y)
			return (1);
		cur++;
	}
	return (0);
}

void	delete_background_line_x(t_fdf *params, t_map tile, int max)
{
	int cur1;
	int cur2;

	cur1 = 1;
	while (tile.line_x[cur1].x == tile.coord.x)
		cur1++;
	while (cur1 < tile.line_x[0].y)
	{
		cur2 = (tile.line_x[cur1].y > 0) ? tile.line_x[cur1].y : 0;
		while (cur2 < max)
			put_pixel_black(params, fill_pos(cur2++, tile.line_x[cur1].x));
		cur1++;
	}
}

void	delete_background_line_y(t_fdf *params, t_map tile, int max)
{
	int cur1;
	int cur2;

	cur1 = 1;
	while (tile.line_y[cur1].x == tile.coord.x)
		cur1++;
	while (cur1 < tile.line_y[0].y)
	{
		cur2 = (tile.line_y[cur1].y > 0) ? tile.line_y[cur1].y : 0;
		while (cur2 < max)
			put_pixel_black(params, fill_pos(cur2++, tile.line_y[cur1].x));
		cur1++;
	}
}

void	delete_background_center(t_fdf *params, int y, int x, int max)
{
	t_map	tile;
	int		s_x;
	int		cur;

	cur = 0;
	tile = MAP_PTR[y][x];
	s_x = MAP_PTR[y][x].coord.x;
	if (tile.line_x)
		cur = tile.line_x[1].y;
	if (tile.line_y && tile.line_y[1].y > cur)
		cur = tile.line_y[1].y;
	if ((tile.line_x && !(tile.line_y)) || (tile.line_y && !(tile.line_x)) ||\
		((!tile.line_y) && !(tile.line_x)))
		cur = tile.coord.y + 1;
	while (cur < max)
		put_pixel_black(params, fill_pos(cur++, s_x));
}

void	delete_background(t_fdf *params, int y, int x)
{
	t_map	tile;
	int		max;

	tile = MAP_PTR[y][x];
	max = tile.coord.y;
	if ((x < params->s_map.x - 1) && max < MAP_PTR[y][x + 1].coord.y)
		max = MAP_PTR[y][x + 1].coord.y;
	if ((y < params->s_map.y - 1) && max < MAP_PTR[y + 1][x].coord.y)
		max = MAP_PTR[y + 1][x].coord.y;
	if ((y < params->s_map.y - 1) && (x < params->s_map.x - 1) && \
		max < MAP_PTR[y + 1][x + 1].coord.y)
		max = MAP_PTR[y + 1][x + 1].coord.y;
	if ((x == (params->s_map.x - 1)) || (y == (params->s_map.y - 1)))
		max = params->s_win.y;
	if (max > params->s_win.y)
		max = params->s_win.y;
	delete_background_center(params, y, x, max);
	if (tile.line_x)
		delete_background_line_x(params, tile, max);
	if (tile.line_y)
		delete_background_line_y(params, tile, max);
}
