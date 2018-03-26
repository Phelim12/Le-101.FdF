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

#include "fdf.h"
#include "function_fdf.h"

void	init_struct_mlx(t_fdf *params)
{
	int s_win_x;
	int s_win_y;

	s_win_x = params->s_win.x;
	s_win_y = params->s_win.y;
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(MLX_PTR, s_win_x, s_win_y, "FdF");
	params->img_ptr = mlx_new_image(MLX_PTR, s_win_x, s_win_y);
	params->mlx_img = mlx_get_data_addr(IMG_PTR, BPP, S_L, ENDIAN);
}

int		refresh_map(int key, t_fdf *params)
{
	char	*img;
	int		cur;

	cur = -1;
	img = params->mlx_img;
	if (key == 53)
	{
		free_map_fdf(params);
		free_file_fdf(params->file_map);
		exit(EXIT_SUCCESS);
	}
	if (modif_params_map(key, params))
		return (0);
	while (++cur < (params->s_win.y * params->s_win.x * 4))
		img[cur] = 0;
	free_map_fdf(params);
	params->map = parsing_map(params, 0);
	print_map_iso(*params);
	mlx_put_image_to_window(MLX_PTR, params->win_ptr, params->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char const *argv[])
{
	t_fdf	params;
	int		error;

	if (!(error = check_error_fdf(argv, argc)))
	{
		params.file_map = parsing_file(argv[1]);
		if (check_error_map_fdf(params.file_map))
			print_error_fdf(argv[0], params.file_map);
	}
	else
		return (print_usage_fdf(argv[0], argv[1], error));
	params.s_win.x = size_win_width();
	params.s_win.y = size_win_height();
	init_struct_mlx(&params);
	params.map = parsing_map(&params, 1);
	print_map_iso(params);
	mlx_put_image_to_window(params.mlx_ptr, WIN_PTR, params.img_ptr, 0, 0);
	mlx_hook(params.win_ptr, 2, 0, refresh_map, &params);
	mlx_loop(params.mlx_ptr);
	return (0);
}
