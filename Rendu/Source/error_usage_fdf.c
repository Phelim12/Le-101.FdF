/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_usage_fdf.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/26 20:27:27 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/26 20:27:27 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "function_fdf.h"

void	print_error_fdf(char const *name, char ***map)
{
	if (ft_strstr(name, "./"))
		ft_putstr_fd((name + 2), 2);
	else
		ft_putstr_fd(name, 2);
	ft_putendl_fd(": Error the map is not true", 2);
	free_file_fdf(map);
	exit(EXIT_SUCCESS);
}

int		check_error_fdf(char const *argv[], int argc)
{
	char	sample[2];
	int		fd;

	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (2);
	else if ((read(fd, sample, 2)) == 0)
	{
		close(fd);
		return (3);
	}
	close(fd);
	return (0);
}

int		print_usage_fdf(const char *name, const char *name_file, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("usage: ", 2);
		if (ft_strstr(name, "./"))
			ft_putstr_fd((name + 2), 2);
		else
			ft_putstr_fd(name, 2);
		ft_putendl_fd(" [file]", 2);
	}
	if (error == 2)
	{
		if (ft_strstr(name, "./"))
			ft_putstr_fd((name + 2), 2);
		else
			ft_putstr_fd(name, 2);
		ft_putstr_fd(": no such file or directory: ", 2);
		ft_putendl_fd(name_file, 2);
	}
	if (error == 3)
	{
		ft_putstr_fd(name_file, 2);
		ft_putendl_fd(": file empty", 2);
	}
	return (0);
}

int		check_error_tile_fdf(char *str)
{
	int cur;

	cur = 0;
	while (ft_isdigit(str[cur]) || str[cur] == '-' || str[cur] == '+')
		cur++;
	if (str[cur] == 0 || str[cur] == ',')
		return (0);
	else
		return (1);
}

int		check_error_map_fdf(char ***map)
{
	int s_x;
	int x;
	int y;

	y = -1;
	s_x = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (check_error_tile_fdf(map[y][x]))
				return (1);
		if (y == 0)
			s_x = x;
		if (x != s_x)
			return (1);
	}
	if (y == 1 && s_x == 1)
		return (1);
	return (0);
}
