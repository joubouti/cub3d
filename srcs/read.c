/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:57:11 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 18:46:53 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*g_errno[5] = {"Couldn't Read The Map",
	"Invalid Map File",
	"Wrong Floor/Ceilling Color",
	"usage: ./cub3d <map-path>",
	"There's More Than One Spawn"};

int		ft_error(int n, int err)
{
	char *error;

	if (n == -1)
	{
		if (err != -1)
		{
			error = ft_strjoin("Error\n", g_errno[err]);
			ft_putstr_fd(error, 2);
			free(error);
		}
		else
			perror("Error");
		exit(-1);
	}
	return (1);
}

int		ft_rgb_hex(char *str)
{
	char		**s;
	int			r;
	int			g;
	int			b;

	s = ft_split(str, ',');
	ft_error((s[3] == NULL) - 1, 2);
	r = ft_atoi(s[0]);
	g = ft_atoi(s[1]);
	b = ft_atoi(s[2]);
	ft_error((r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256)
	- 1, 2);
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int		ft_check_arg(char *line, char **r, int fd)
{
	if (ft_strncmp(r[0], "R", 1) == 0)
		(g_g.win_w = ft_atoi(r[1])) &&
		(g_g.win_h = ft_atoi(r[2]));
	else if (ft_strncmp(r[0], "NO", 2) == 0)
		(int)g_tx.no ? ft_error(-1, 1) : (g_tx.no = ft_strdup(r[1])) || 1;
	else if (ft_strncmp(r[0], "SO", 2) == 0)
		(int)g_tx.so ? ft_error(-1, 1) : (g_tx.so = ft_strdup(r[1])) || 1;
	else if (ft_strncmp(r[0], "WE", 2) == 0)
		(int)g_tx.we ? ft_error(-1, 1) : (g_tx.we = ft_strdup(r[1])) || 1;
	else if (ft_strncmp(r[0], "EA", 2) == 0)
		(int)g_tx.ea ? ft_error(-1, 1) : (g_tx.ea = ft_strdup(r[1])) || 1;
	else if (ft_strncmp(r[0], "S", 1) == 0)
		(int)g_tx.s ? ft_error(-1, 1) : (g_tx.s = ft_strdup(r[1])) || 1;
	else if (ft_strncmp(r[0], "F", 1) == 0)
		(int)g_tx.f ? ft_error(-1, 1) : (g_tx.f = ft_rgb_hex(r[1]));
	else if (ft_strncmp(r[0], "C", 1) == 0)
		(int)g_tx.c ? ft_error(-1, 1) : (g_tx.c = ft_rgb_hex(r[1]));
	else if (ft_strncmp(r[0], "1", 1) == 0)
		return (ft_create_maze(line, fd));
	else
		ft_error(-1, 1);
	return (0);
}

void	ft_maze(char *file)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;
	char	**s;

	ft_error((fd = open(file, O_RDONLY)), -1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strncmp(line, "", 1) == 0)
			continue ;
		i = 0;
		s = ft_split(line, ' ');
		ft_check_arg(line, s, fd);
		free(line);
		while (s[i])
			free(s[i++]);
		free(s);
	}
	(g_g.win_w < 1 || g_g.win_h < 1 || !g_g.maze_size.x || !g_tx.no || !g_tx.so
	|| !g_tx.we || !g_tx.ea ||
	!g_tx.s || !g_tx.f || !g_tx.c) ? ft_error(-1, 1) : ft_error(ret, 0);
	if (g_g.win_w > 2560 || g_g.win_h > 1440)
		(g_g.win_w = 2560) &&
		(g_g.win_h = 1440);
}
