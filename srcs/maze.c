/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:07:32 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 18:40:50 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_remove_space(char *line, int f)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (line[i])
		(line[i++] == ' ' ? j++ : 0);
	new = malloc(j + 1);
	i = -1;
	j = 0;
	while (line[++i])
		if (line[i] != ' ')
			new[j++] = line[i];
	new[j] = 0;
	if (f)
		free(line);
	return (new);
}

void	ft_fill_maze(char *maze, int i, int cx, int cy)
{
	static char	a = 0;

	if (maze[i] == '1' || maze[i] == '2')
		g_g.maze[cx][cy] = maze[i] - 48;
	else if (maze[i] == 'N' || maze[i] == 'S' || maze[i] == 'W' ||
	maze[i] == 'E')
	{
		if (a++ != 0)
			ft_error(-1, 4);
		g_g.pos.x = cx * 64 + 32;
		g_g.pos.y = cy * 64 + 32;
		if (maze[i] == 'N')
			g_g.rot = 180;
		else if (maze[i] == 'S')
			g_g.rot = 0;
		else if (maze[i] == 'W')
			g_g.rot = -90;
		else
			g_g.rot = 90;
	}
	else if (maze[i] != '0')
		ft_error(-1, 1);
}

int		ft_make_maze(char *maze)
{
	int		cy;
	int		cx;
	int		i;

	cy = 0;
	cx = 0;
	i = 0;
	g_g.maze = ft_calloc(g_g.maze_size.x, sizeof(char *));
	while (i < g_g.maze_size.x)
		g_g.maze[i++] = ft_calloc(g_g.maze_size.y, sizeof(char));
	i = 0;
	while (maze[i])
	{
		if (i != 0 && i % ((int)g_g.maze_size.x) == 0)
		{
			cy++;
			cx = 0;
		}
		ft_fill_maze(maze, i, cx, cy);
		cx++;
		i++;
	}
	return (0);
}

int		ft_create_maze(char *line, int fd)
{
	static int		cy = 1;
	static size_t	cx = 0;
	char			*maze;
	char			*l;
	size_t			i;

	i = 0;
	cx = ft_strlen(
	maze = ft_remove_space(line, 0));
	while (maze[i] != 0)
		(maze[i] == '1') ? i++ : ft_error(-1, 1);
	while (get_next_line(fd, &l) && cy++ && (l = ft_remove_space(l, 1)))
	{
		if (l[0] != '1' || l[ft_strlen(l) - 1] != '1' || ft_strlen(l) != cx)
			ft_error(l[0] ? -1 : 0, 1);
		line = maze;
		maze = ft_strjoin(maze, l);
		while (l[i] != 0 || l[i] == '1')
			i++;
		free(line);
		free(l);
	}
	(i != cx) ? ft_error(-1, 1) : 1;
	g_g.maze_size = (t_vector2){cx, cy};
	return (ft_make_maze(maze));
}
