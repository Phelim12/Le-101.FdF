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

void	init_struct_mlx(t_fdf *params)
{
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(params->mlx_ptr, params->s_win.x, params->s_win.y, "FdF");
	params->img_ptr = mlx_new_image(params->mlx_ptr, params->s_win.x, params->s_win.y);
	params->mlx_img = mlx_get_data_addr(params->img_ptr, &(params->bpp), &(params->s_l), &(params->endian));
}

int refresh_fdf(int key, t_fdf *params)
{
	char *img;
	int cur;

	cur = -1;
	img = params->mlx_img;
	if (key == 69)
		params->s_line += 2;
	if (key == 78)
		params->s_line -= 2;
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
		params->s_line = 3;
	while (++cur < (params->s_win.y * params->s_win.x * 4))
		img[cur] = 0;
	params->map = parsing_map(params, 0);
	draw_map_2d(*params);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->img_ptr, 0, 0);
	return (0);

}

int		main(int argc, char const *argv[])
{
	t_fdf	params;
	int		error;
	
	params.s_win.y = 1000;
	params.s_win.x = 1500;
	if (!(error = check_error_fdf(argv)))
		params.file_map = parsing_file(argv[1]);
	else
		return (print_usage_fdf(argv[1], error));
	params.map = parsing_map(&params, 1);
	init_struct_mlx(&params);
	draw_map_2d(params);
	mlx_put_image_to_window(params.mlx_ptr, params.win_ptr, params.img_ptr, 0, 0);
	mlx_hook(params.win_ptr, 2, 0, refresh_fdf, &params);
	mlx_loop(params.mlx_ptr);
	return (0);
} 
