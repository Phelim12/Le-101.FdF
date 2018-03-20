/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prasing_file_fdf.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/19 16:37:57 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/19 16:37:57 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "FdF.h"

int		ft_line_file(const char *name)
{
	char	sample[1024];
	int		n_read;
	int		cur;
	int		ret;
	int		fd;

	ret = 0;
	fd = open(name, O_RDONLY);
	while ((n_read = read(fd, sample, 1024)))
	{
		cur = -1;
		sample[n_read] = 0;
		while (sample[++cur])
			if (sample[cur] == '\n')
				ret++;
	}
	close(fd);
	return (ret + 5);
}

char	***parsing_file(const char *name)
{
	char	***ret;
	char	*line;
	int		cur;
	int 	fd;

	cur = 0;
	ret = (char ***)malloc(sizeof(char **) * (ft_line_file(name)));
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ret[cur++] = ft_strsplit(line, ' ');
		free(line);
	}
	ret[cur] = NULL;
	return (ret);
}