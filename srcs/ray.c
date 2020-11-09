/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:24:21 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 18:31:41 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		g_colors[5] = {'W', 'E', 'N', 'S', 'P'};

int			ft_check_corner_two(int d1, int d2, int rx, int ry)
{
	if (g_g.maze[rx][ry] == 1)
		return (((d1 > d2 && (rx > 0 && g_g.maze[rx - 1][ry] == 0)) ||
		(ry > 0 && g_g.maze[rx][ry - 1])) ? g_colors[0] : g_colors[2]);
	else if (g_g.maze[rx - 1][ry] == 1)
		return (d1 > d2 || (ry > 0 && g_g.maze[rx - 1][ry - 1])
		? g_colors[1] : g_colors[2]);
	else if (g_g.maze[rx][ry - 1] == 1)
		return ((d1 > d2) && (ry > 0 && ry > 0 && g_g.maze[rx - 1][ry - 1] == 0)
		? g_colors[0] : g_colors[3]);
	else if (g_g.maze[rx - 1][ry - 1] == 1)
		return (d1 > d2 ? g_colors[1] : g_colors[3]);
	return (0);
}

int			ft_check_corner(int rx, int ry)
{
	float		d1;
	float		d2;
	t_vector4	c;

	if (g_g.maze[rx][ry] == 1)
		c = (t_vector4){rx * 64 + 32, ry * 64, rx * 64, ry * 64 + 32};
	else if (g_g.maze[rx - 1][ry] == 1)
		c = (t_vector4){rx * 64 - 32, ry * 64, rx * 64, ry * 64 + 32};
	else if (g_g.maze[rx][ry - 1] == 1)
		c = (t_vector4){rx * 64 + 32, ry * 64, rx * 64, ry * 64 - 32};
	else if (g_g.maze[rx - 1][ry - 1] == 1)
		c = (t_vector4){rx * 64 - 32, ry * 64, rx * 64, ry * 64 - 32};
	d1 = sqrt(pow(c.x - g_g.pos.x, 2) + pow(c.y - g_g.pos.y, 2));
	d2 = sqrt(pow(c.w - g_g.pos.x, 2) + pow(c.h - g_g.pos.y, 2));
	return (ft_check_corner_two(d1, d2, rx, ry));
}

int			ft_co(int rx, int ry, char w)
{
	if (w == 'x')
	{
		if (rx == g_g.maze_size.x && g_g.maze[rx - 1][ry] == 1)
			return (1);
	}
	else if (w == 'y')
	{
		if (ry == g_g.maze_size.y && g_g.maze[rx][ry - 1] == 1)
			return (1);
	}
	return (0);
}

int			ft_check_rayhit(int x, int y, int i)
{
	int rx;
	int ry;

	rx = x / 64;
	ry = y / 64;
	if (x >= 0 && y >= 0 && (x % 64 == 0 || y % 64 == 0) &&
	rx < (g_g.maze_size.x) && rx >= 0 &&
	(ry < g_g.maze_size.y) && ry >= 0 && ft_check_sprite(x, y, i))
	{
		if (x % 64 == 0 && y % 64 == 0 && (g_g.maze[rx][ry] == 1 || (rx > 0 &&
		g_g.maze[rx - 1][ry]) == 1 || (ry > 0 && g_g.maze[rx][ry - 1] == 1) ||
		(rx > 0 && ry > 0 && g_g.maze[rx - 1][ry - 1] == 1)))
			return (ft_check_corner(rx, ry));
		else if (x % 64 == 0 && g_g.maze[rx][ry] == 1)
			return (g_colors[0]);
		else if (x % 64 == 0 && (rx > 0 && g_g.maze[rx - 1][ry] == 1))
			return (g_colors[1]);
		else if (y % 64 == 0 && g_g.maze[rx][ry] == 1)
			return (g_colors[2]);
		else if (y % 64 == 0 && (ry > 0 && g_g.maze[rx][ry - 1] == 1))
			return (g_colors[3]);
	}
	return (0);
}

void		ft_check_ray(float i, t_vector3 hit, float a)
{
	float	d;
	float	h;
	int		txoffsetx;

	txoffsetx = 0;
	if (hit.x >= 0)
	{
		a = fabs(((float)g_g.fov * i / (float)g_g.win_w) - (float)g_g.fov
		/ 2);
		d = sqrt(pow(hit.x - g_g.pos.x, 2) + pow(hit.y - g_g.pos.y,
		2)) * cos(a * g_dg);
		h = (64 * g_g.win_h) / (d + 1);
		if (hit.z == 'W')
			txoffsetx = ((int)hit.y) % 64;
		else if (hit.z == 'S')
			txoffsetx = ((int)hit.x) % 64;
		else if (hit.z == 'E')
			txoffsetx = 64 - ((int)hit.y) % 64;
		else if (hit.z == 'N')
			txoffsetx = 64 - ((int)hit.x) % 64;
		ft_draw_texture(&g_g.img, (t_vector3){i, (g_g.win_h - h) / 2, h},
		txoffsetx, hit.z);
	}
}
