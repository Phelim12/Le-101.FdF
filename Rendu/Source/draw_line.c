/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 20:44:20 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/13 20:44:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"
/*
'couleur de départ
    r1 = 170
    g1 = 30
    b1 = 30
'couleur d'arrivée
    r2 = 250
    g2 = 235
    b2 = 235
'pour chaque canal, calcul du différenciel entre chaque teinte (nbVal est le nombre de teintes du dégradé)
    dr = Int((r2 - r1) / nbVal)
    dg = Int((g2 - g1) / nbVal)
    db = Int((b2 - b1) / nbVal)
 
'on boucle pour remplir un tableau contenant toutes les valeurs des teintes
    For i = 0 To nbVal - 1
        color(i) = RGB(r2, g2, b2)
        r2 = r2 - dr
        g2 = g2 - dg
        b2 = b2 - db
    Next
    void	put_pixel_image(char *mlx_img, t_draw info, int pix)
{
	unsigned char	*col_a;
	unsigned char	*col_b;
	int				cur;

	if (info.a.y < 0 || info.a.x < 0 || info.a.y >= info.s_win.y || info.a.x >= info.s_win.x)
		return ;
	cur = (4 * info.a.x) + (info.a.y * (info.s_win.x * 4));
	if (cur > (info.s_win.x * info.s_win.y * 4))
		return ;
	col_a = (unsigned char *)ft_strnew(5);
	col_b = (unsigned char *)ft_strnew(5);
	ft_memcpy(col_a, &info.col_a, 4);
	ft_memcpy(col_b, &info.col_b, 4);
	mlx_img[cur] = (col_b[0] != col_a[0]) ? (((pix + 1) * FT_ABS(col_b[0] - col_a[0])) / info.size) : (char)col_a[0];
	mlx_img[cur + 1] = (col_b[1] != col_a[1]) ? (((pix + 1) * FT_ABS(col_b[1] - col_a[1])) / info.size) : (char)col_a[1];
	mlx_img[cur + 2] = (col_b[2] != col_a[2]) ? (((pix + 1) * FT_ABS(col_b[2] - col_a[2])) / info.size) : (char)col_a[2];
	mlx_img[cur + 3] = 0;
}
*/

void	put_pixel_image(char *mlx_img, t_draw info, int pix)
{
	unsigned char	*col_a;
	unsigned char	*col_b;
	int				cur;

	if (info.a.y < 0 || info.a.x < 0 || info.a.y >= info.s_win.y || info.a.x >= info.s_win.x)
		return ;
	cur = (4 * info.a.x) + (info.a.y * (info.s_win.x * 4));
	if (cur > (info.s_win.x * info.s_win.y * 4))
		return ;
	col_a = (unsigned char *)ft_strnew(5);
	col_b = (unsigned char *)ft_strnew(5);
	ft_memcpy(col_a, &info.col_b, 4);
	ft_memcpy(col_b, &info.col_a, 4);
	if (FT_ABS(col_b[0] - col_a[0]) > info.size)
		mlx_img[cur] = (col_b[0] != col_a[0]) ? (col_a[0] - ((FT_ABS(col_b[0] - col_a[0]) / info.size) * pix)) : (char)col_a[0];
	else
		mlx_img[cur] = (char)col_a[0];
	if (FT_ABS(col_b[1] - col_a[1]) > info.size)
		mlx_img[cur + 1] = (col_b[1] != col_a[1]) ? (col_a[1] - ((FT_ABS(col_b[1] - col_a[1]) / info.size) * pix)) : (char)col_a[1];
	else
		mlx_img[cur + 1] = (char)col_a[1];
	if (FT_ABS(col_b[2] - col_a[2]) > info.size)
		mlx_img[cur + 2] = (col_b[2] != col_a[2]) ? (col_a[2] - ((FT_ABS(col_b[2] - col_a[2]) / info.size) * pix)) : (char)col_a[2];
	else
		mlx_img[cur + 2] = (char)col_a[2];
	mlx_img[cur + 3] = 0;
}


int		size_line_vertical(t_draw info)
{
	int		ret;

	ret = 1;
	info.count = (info.dis_y / 2);
	while (ret++ <= info.dis_y)
	{
		info.a.y += info.yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += info.xinc;
		}
	}
	return (ret);
}

int		size_line_horizontal(t_draw info)
{
	int		ret;

	ret = 1;
	info.count = (info.dis_x / 2);
	while (ret++ <= info.dis_x)
	{
		info.a.x += info.xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += info.yinc;
		}
	}
	return (ret);
}

t_pos	*draw_line_vertical(char *mlx_img, t_draw info)
{
	t_pos	*ret;
	int		cur;

	cur = 1;
	info.count = (info.dis_y / 2);
	info.size = size_line_vertical(info);
	put_pixel_image(mlx_img, info, cur);
	ret = (t_pos*)malloc(sizeof(t_pos) * (info.size + 2));
	while (cur++ <= info.dis_y)
	{
		info.a.y += info.yinc;
		info.count += info.dis_x;
		if (info.count >= info.dis_y)
		{
			info.count -= info.dis_y;
			info.a.x += info.xinc;
		}
		put_pixel_image(mlx_img, info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z)
		rev_line(ret);
	return (ret);
}

t_pos	*draw_line_horizontal(char *mlx_img, t_draw info)
{
	t_pos	*ret;
	int		cur;

	cur = 1;
	info.count = (info.dis_x / 2);
	info.size = size_line_horizontal(info);
	put_pixel_image(mlx_img, info, cur);
	ret = (t_pos*)malloc(sizeof(t_pos) * (info.size + 2));
	while (cur++ <= info.dis_x)
	{
		info.a.x += info.xinc;
		info.count += info.dis_y;
		if (info.count >= info.dis_x)
		{
			info.count -= info.dis_x;
			info.a.y += info.yinc;
		}
		put_pixel_image(mlx_img, info, cur);
		ret[cur - 2] = info.a;
	}
	ret[cur - 2] = fill_pos(-1, -1);
	if (info.a.z < info.b.z)
		rev_line(ret);
	return (ret);
}

t_pos	*draw_line(t_fdf params, t_map a, t_map b)
{
	t_draw	info;

	info.a = a.coord;
	info.b = b.coord;
	info.col_a = a.color;
	info.col_b = b.color;
	info.s_win = params.s_win;
	info.dis_y = FT_ABS((info.a.y - info.b.y));
	info.dis_x = FT_ABS((info.a.x - info.b.x));
	info.xinc = ((info.a.x - info.b.x) > 0) ? -1 : 1;
	info.yinc = ((info.a.y - info.b.y) > 0) ? -1 : 1;
	if (info.dis_x > info.dis_y)
		return (draw_line_horizontal(params.mlx_img, info));
	else
		return (draw_line_vertical(params.mlx_img, info));
}









