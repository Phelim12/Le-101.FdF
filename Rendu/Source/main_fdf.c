/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_fdf.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/12 19:22:32 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/20 16:39:50 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

void	put_pixel_black(t_fdf *params, t_pos print, int max)
{
	unsigned char	*color;
	char			*img;
	int				cur;

	color = (unsigned char *)ft_strnew(5);
	//if (max == params->s_win.y)
	//	ft_memcpy(color, &print.z, 4);
	img = (char *)params->mlx_img;
	if (print.y < 0 || print.x < 0 || print.y >= params->s_win.y || print.x >= params->s_win.x)
		return ;
	cur = (4 * print.x) + (print.y * (params->s_win.x * 4));
	if (cur > (params->s_win.x * params->s_win.y * 4))
		return ;
	img[cur] = color[0];
	img[cur + 1] = color[1];
	img[cur + 2] = color[2];
	img[cur + 3] = 0;
}

void	draw_map_2d(t_fdf params)
{
	int		y;
	int		x;

	y = -1;
	while (MAP[++y])
	{
		x = -1;
		while (MAP[y][++x].stop)
		{
			MAP[y][x].line_x = NULL;
			MAP[y][x].line_y = NULL;
			if (x < (params.s_map.x - 1))
				MAP[y][x].line_x = draw_line(params, MAP[y][x], MAP[y][1 + x]);
			if (y < (params.s_map.y - 1))
				MAP[y][x].line_y = draw_line(params, MAP[y][x], MAP[y + 1][x]);
			delete_background(&params, y, x);
		}
	}
}


t_mlx	init_struct_mlx(t_fdf *params)
{
	t_mlx	ret;

	ret.mlx_ptr = mlx_init();
	ret.win_ptr = mlx_new_window(ret.mlx_ptr, params->s_win.x, params->s_win.y, "FdF");
	ret.img_ptr = mlx_new_image(ret.mlx_ptr, params->s_win.x, params->s_win.y);
	params->mlx_img = mlx_get_data_addr(ret.img_ptr, &(ret.bpp), &(ret.s_l), &(ret.endian));
	return (ret);
}

int		main(int argc, char const *argv[])
{
	t_mlx	struct_mlx;
	t_fdf	params;
	int		error;
	
	params.s_win.y = 1000;
	params.s_win.x = 1500;
	if (!(error = check_error_fdf(argv)))
		params.file_map = parsing_file(argv[1]);
	else
		return (print_usage_fdf(argv[1], error));
	params.map = parsing_map(&params);
	struct_mlx = init_struct_mlx(&params);
	draw_map_2d(params);
	mlx_put_image_to_window(struct_mlx.mlx_ptr, struct_mlx.win_ptr, struct_mlx.img_ptr, 0, 0);
	mlx_loop(struct_mlx.mlx_ptr);
	return (0);
} 
