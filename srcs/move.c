/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:13:33 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 21:40:18 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			g_hold[4] = {-1, -1, -1, -1};

void	ft_move(char c)
{
	t_vector2 d;

	d = (t_vector2){cos(g_g.rot * g_dg) * g_g.speed, sin(g_g.rot * g_dg) *
	g_g.speed};
	if (c == 'l')
	{
		g_g.pos.x -= ft_isin(g_g.pos.x - d.x - 9 * s(d.x), g_g.pos.y) ? d.x : 0;
		g_g.pos.y += ft_isin(g_g.pos.x, g_g.pos.y + d.y + 9 * s(d.y)) ? d.y : 0;
	}
	else if (c == 'r')
	{
		g_g.pos.x += ft_isin(g_g.pos.x + d.x + 9 * s(d.x), g_g.pos.y) ? d.x : 0;
		g_g.pos.y -= ft_isin(g_g.pos.x, g_g.pos.y - d.y - 9 * s(d.y)) ? d.y : 0;
	}
	else if (c == 'f')
	{
		g_g.pos.x += ft_isin(g_g.pos.x + d.y + 9 * s(d.y), g_g.pos.y) ? d.y : 0;
		g_g.pos.y += ft_isin(g_g.pos.x, g_g.pos.y + d.x + 9 * s(d.x)) ? d.x : 0;
	}
	else if (c == 'b')
	{
		g_g.pos.x -= ft_isin(g_g.pos.x - d.y - 9 * s(d.y), g_g.pos.y) ? d.y : 0;
		g_g.pos.y -= ft_isin(g_g.pos.x, g_g.pos.y - d.x - 9 * s(d.x)) ? d.x : 0;
	}
}

void	ft_movement(int key)
{
	if (key == 53)
		ft_close();
	else if (key == 123)
		g_g.rot += 0.5 * g_g.speed;
	else if (key == 124)
		g_g.rot -= 0.5 * g_g.speed;
	else if (key == 0)
		ft_move('r');
	else if (key == 2)
		ft_move('l');
	else if (key == 1)
		ft_move('b');
	else if (key == 13)
		ft_move('f');
}

int		ft_keypress(int keycode)
{
	int i;
	int p;

	i = 0;
	p = -1;
	while (i < 4)
	{
		if (g_hold[i] != -1 && g_hold[i] == keycode)
			return (0);
		if (g_hold[i] == -1 && keycode != -1 && p == -1)
			p = i;
		i++;
	}
	if (p != -1)
		g_hold[p] = keycode;
	return (0);
}

void	ft_keyhold(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (g_hold[i] != -1)
			ft_movement(g_hold[i]);
		i++;
	}
}

int		ft_keyrelease(int keycode)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (g_hold[i] != -1 && g_hold[i] == keycode)
			g_hold[i] = -1;
		i++;
	}
	return (0);
}
