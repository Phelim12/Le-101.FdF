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

#include "FdF.h"

void	delete_background_line_x(t_fdf *params, t_map tile, int max)
{
	int cur1;
	int cur2;

	cur1 = 0;
	while (tile.line_x[cur1].x != -1 || tile.line_x[cur1].y != -1)
	{
		cur2 = tile.line_x[cur1].y;
		while (tile.line_x[cur1].x != tile.line_x[cur1 + 1].x && cur2 < max + 10)
			put_pixel_black(params, fill_pos(++cur2, tile.line_x[cur1].x), max);
		cur1++;
	}
}

void	delete_background_line_y(t_fdf *params, t_map tile, int max)
{
	int cur1;
	int cur2;

	cur1 = 0;
	while (tile.line_y[cur1].x != -1 || tile.line_y[cur1].y != -1)
	{
		cur2 = tile.line_y[cur1].y;
		while (tile.line_y[cur1].x != tile.line_y[cur1 + 1].x && cur2 < max + 10)
			put_pixel_black(params, fill_pos(++cur2, tile.line_y[cur1].x), max);
		cur1++;
	}
}

void	delete_background_center(t_fdf *params, t_map tile, int max)
{
	int cur;

	cur = 0;
	while ((tile.line_x && tile.coord.x == tile.line_x[cur].x) ||
	 		(tile.line_y && tile.coord.x == tile.line_y[cur].x))
		cur++;
	cur += tile.coord.y;
	while (cur++ < max)
		put_pixel_black(params, fill_pos(cur, tile.coord.x), max);
}

void	delete_background(t_fdf *params, int y, int x)
{
	t_map	tile;
	int		max;

	tile = params->map[y][x];
	max = params->s_win.y;
	if (tile.line_x && tile.line_y)
		max = params->map[y + 1][x + 1].coord.y;
	delete_background_center(params, tile, max);
	if (tile.line_x)
		delete_background_line_x(params, tile, max);
	if (tile.line_y)
		delete_background_line_y(params, tile, max);
}
