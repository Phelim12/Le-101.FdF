/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_map_fdf.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 17:46:42 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/24 17:46:42 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

void	free_line_map(t_map *tile)
{
	if (tile->line_x)
		free(tile->line_x);
	if (tile->line_y)
		free(tile->line_y);
}

void	delete_first_line(t_fdf *params)
{
	char	*img;
	int		stop;
	int		cur;

	cur = -1;
	img = params->mlx_img;
	stop = (params->s_win.x * 4);
	while (++cur < stop)
		img[cur] = 0;
}

int		faster_display(t_fdf params, int y, int x)
{
	int s_win_x;
	int s_win_y;

	s_win_x = params.s_win.x;
	s_win_y = params.s_win.y;
	if ((x + 1) < (params.s_map.x - 1) && (y + 1) < (params.s_map.y - 1))
	{
		if (MAP_YX.coord.y < 0 && MAP_PX.coord.y < 0 &&
			MAP[y + 1][x + 1].coord.y < 0 && MAP_PY.coord.y < 0)
			return (0);
		if (MAP_YX.coord.x < 0 && MAP_PX.coord.x < 0 &&
			MAP[y + 1][x + 1].coord.x < 0 && MAP_PY.coord.x < 0)
			return (0);
		if (MAP_YX.coord.x > s_win_x && MAP_PX.coord.x > s_win_x &&
			MAP[y + 1][x + 1].coord.x > s_win_x && MAP_PY.coord.x > s_win_x)
			return (0);
		if (MAP_YX.coord.y > s_win_y && MAP_PX.coord.y > s_win_y &&
			MAP[y + 1][x + 1].coord.y > s_win_y && MAP_PY.coord.y > s_win_y)
			return (0);
	}
	return (1);
}

void	print_map_iso(t_fdf params)
{
	int		y;
	int		x;

	y = -1;
	while (MAP[++y])
	{
		x = -1;
		while (MAP[y][++x].stop)
		{
			MAP_YX.line_x = NULL;
			MAP_YX.line_y = NULL;
			if (x < (params.s_map.x - 1) && faster_display(params, y, x))
				MAP_YX.line_x = (MAP_YX.coord.y > MAP_PX.coord.y) ? draw_line(\
				&params, MAP_PX, MAP_YX) : draw_line(&params, MAP_YX, MAP_PX);
			if (y < (params.s_map.y - 1) && faster_display(params, y, x))
				MAP_YX.line_y = (MAP_YX.coord.y > MAP_PY.coord.y) ? draw_line(\
				&params, MAP_PY, MAP_YX) : draw_line(&params, MAP_YX, MAP_PY);
			delete_background(&params, y, x);
			free_line_map(&MAP_YX);
		}
	}
	delete_first_line(&params);
}
