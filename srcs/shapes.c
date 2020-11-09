/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:13:21 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 20:15:46 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_draw_rectangle(t_image *img_ptr, t_vector2 p, t_vector2 s,
int color)
{
	int i;
	int j;

	i = 0;
	while (i < s.x)
	{
		j = 0;
		while (j < s.y)
		{
			ft_setpixel(img_ptr, p.x + i, p.y + j, color);
			j++;
		}
		i++;
	}
}

t_vector3	ft_draw_ray(t_vector3 p0, t_vector2 p1)
{
	t_vector2	d;
	t_vector4	m;
	int			steps;
	int			i;

	i = 0;
	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	steps = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	m.w = (int)d.x / (float)steps;
	m.h = (int)d.y / (float)steps;
	m.x = p0.x;
	m.y = p0.y;
	while (i <= steps)
	{
		if ((d.x = ft_check_rayhit(round(m.x), round(m.y), p0.z)))
			return ((t_vector3){round(m.x), round(m.y), d.x});
		m.x += m.w;
		m.y += m.h;
		i++;
	}
	return ((t_vector3){-1, -1, -1});
}

void		ft_setpixel(t_image *img_ptr, int x, int y, int color)
{
	int	*p;
	int i;

	if (x >= img_ptr->w || x < 0 || y >= img_ptr->h || y < 0)
		return ;
	i = x + (img_ptr->sl / 4) * y;
	p = (int *)img_ptr->data;
	p[i] = color;
}

int			ft_getpixel(t_image *img_ptr, int x, int y)
{
	int	*p;
	int i;

	if (x >= img_ptr->w || x < 0 || y >= img_ptr->h || y < 0)
		return (-1);
	i = x + (img_ptr->sl / 4) * y;
	p = (int *)img_ptr->data;
	return (p[i]);
}

int	g_grid_size = 64;

void		ft_draw_grid(t_image *img_ptr)
{
	int i;
	int j;

	i = 0;
	while (i <= g_g.win_w)
	{
		j = 0;
		while (j <= g_g.win_h)
			ft_setpixel(img_ptr, i, j++, 0x00999999);
		i += g_grid_size;
	}
	j = 0;
	while (j <= g_g.win_h)
	{
		i = 0;
		while (i <= g_g.win_w)
			ft_setpixel(img_ptr, i++, j, 0x00999999);
		j += g_grid_size;
	}
}
