/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_fdf_01.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/26 18:52:42 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/26 18:52:42 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

t_pos	fill_pos(int y, int x)
{
	t_pos ret;

	ret.y = y;
	ret.x = x;
	return (ret);
}

int		size_win_width(void)
{
	int		ret;
	char	*line;

	ret = 0;
	while (ret > 3840 || ret < 500)
	{
		ft_printf("Enter the width of the window (max - 3840, min - 500): ");
		if ((get_next_line(1, &line)) == 1)
		{
			ret = ft_atoi(line);
			free(line);
		}
		else
			ft_printf("\n");
	}
	return (ret);
}

int		size_win_height(void)
{
	int		ret;
	char	*line;

	ret = 0;
	while (ret > 2160 || ret < 500)
	{
		ft_printf("Enter the height of the window (max - 2160, min - 500): ");
		if ((get_next_line(1, &line)) == 1)
		{
			ret = ft_atoi(line);
			free(line);
		}
		else
			ft_printf("\n");
	}
	return (ret);
}
