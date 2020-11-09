/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:35:55 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 16:41:19 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	g_tx = {NULL, NULL, NULL, NULL, NULL, 0, 0};
t_image		g_sprite;
t_list		*g_sprites = NULL;

void	ft_draw_texture(t_image *img_ptr, t_vector3 p, int offsetx, int face)
{
	int		color;
	int		h;
	int		*c;
	t_image	*tx;
	int		offsety;

	h = 0;
	if (face == 'W')
		tx = &g_g.tex[0];
	else if (face == 'E')
		tx = &g_g.tex[1];
	else if (face == 'N')
		tx = &g_g.tex[2];
	else
		tx = &g_g.tex[3];
	c = (int *)tx->data;
	while (h < p.z)
	{
		if ((p.x < 0 || p.x >= img_ptr->w || (p.y + h) < 0 || (p.y + h) >=
		img_ptr->h) && ++h)
			continue;
		offsety = (h * ((float)tx->h / p.z));
		color = c[((tx->sl / 4) * offsety) + offsetx * (tx->w / 64)];
		ft_setpixel(img_ptr, p.x, p.y + h++, color);
	}
}

void	ft_loadtextures(void)
{
	if (!(g_g.tex[0].ptr = mlx_xpm_file_to_image(g_g.mlx_ptr, g_tx.we,
	&g_g.tex[0].w, &g_g.tex[0].h)) || !(g_g.tex[1].ptr = mlx_xpm_file_to_image(
	g_g.mlx_ptr, g_tx.ea, &g_g.tex[1].w, &g_g.tex[1].h)) || !(g_g.tex[2].ptr =
	mlx_xpm_file_to_image(g_g.mlx_ptr, g_tx.no, &g_g.tex[2].w, &g_g.tex[2].h))
	|| !(g_g.tex[3].ptr = mlx_xpm_file_to_image(g_g.mlx_ptr, g_tx.so,
	&g_g.tex[3].w, &g_g.tex[3].h)) || !(g_sprite.ptr = mlx_xpm_file_to_image(
	g_g.mlx_ptr, g_tx.s, &g_sprite.w, &g_sprite.h)))
		ft_error(-1, 1);
	g_g.tex[0].data = mlx_get_data_addr(g_g.tex[0].ptr, &g_g.tex[0].bpp,
	&g_g.tex[0].sl, &g_g.tex[0].endian);
	g_g.tex[1].data = mlx_get_data_addr(g_g.tex[1].ptr, &g_g.tex[1].bpp,
	&g_g.tex[1].sl, &g_g.tex[1].endian);
	g_g.tex[2].data = mlx_get_data_addr(g_g.tex[2].ptr, &g_g.tex[2].bpp,
	&g_g.tex[2].sl, &g_g.tex[2].endian);
	g_g.tex[3].data = mlx_get_data_addr(g_g.tex[3].ptr, &g_g.tex[3].bpp,
	&g_g.tex[3].sl, &g_g.tex[3].endian);
	g_sprite.data = mlx_get_data_addr(g_sprite.ptr, &g_sprite.bpp,
	&g_sprite.sl, &g_sprite.endian);
}

const float	g_rd = 180 / M_PI;

int		ft_draw_sprite(t_sprite *sp)
{
	int		h;
	int		color;
	int		*c;
	int		offsety;

	h = 0;
	c = (int *)g_sprite.data;
	sp->offset = (float)(sp->offset) * g_sprite.w;
	if (sp->offset < 0.0f || sp->offset >= g_sprite.w)
		return (0);
	while (h < sp->z.y)
	{
		if ((sp->i < 0 || sp->i >= g_g.img.w || (sp->z.x + h) < 0 ||
		(sp->z.x + h) >=
		g_g.img.h) && ++h)
			continue;
		offsety = (h * ((float)g_sprite.h / sp->z.y));
		color = ft_getpixel(&g_sprite, sp->offset, offsety);
		if (color != 0x980088)
			ft_setpixel(&g_g.img, sp->i, sp->z.x + h, color);
		h++;
	}
	return (1);
}

void	ft_calc_sprite(float x, float y, int i, t_vector2 r)
{
	t_vector2	rt;
	t_vector2	dc;
	t_vector2	rot;
	t_sprite	*sp;

	if (ft_sprite_rendered(r, i))
		return ;
	dc = (t_vector2){g_g.pos.x - (r.x * 64 + 32), g_g.pos.y - (r.y * 64 + 32)};
	rt.x = atan2(dc.y, dc.x) * g_rd + 180;
	rt.y = g_g.fov * ((float)i / g_g.win_w);
	rt.y = fmod(90 - g_g.rot + (rt.y - g_g.fov / 2), 360.0f);
	x = (sqrt(pow(dc.x, 2) + pow(dc.y, 2)));
	rot.x = atan(32.0f / (float)x) * g_rd;
	if ((rot.y = fmod(rt.y - rt.x, 360.0)) < -180)
		rot.y += 360;
	else if (rot.y >= 180)
		rot.y -= 360;
	y = (float)(64 * g_g.win_h) / ((float)x + 1);
	if ((rt.x = (rot.y / (float)rot.x + 1.0f) / 2.0f) >= 0.0f && rt.x < 1.0f)
	{
		sp = ft_newsprite((t_vector2){(g_g.win_h - y) / 2.0f, y}, r, i,
		(t_vector2){rt.x, x});
		ft_sorted_list_insert(&g_sprites, sp, ft_cmp);
	}
}

int		ft_check_sprite(int x, int y, int i)
{
	int		rx;
	int		ry;

	rx = x / 64;
	ry = y / 64;
	if (x % 64 == 0 && g_g.maze[rx][ry] == 2)
		ft_calc_sprite(x, y, i, (t_vector2){rx, ry});
	else if (x % 64 == 0 && rx > 0 && g_g.maze[rx - 1][ry] == 2)
		ft_calc_sprite(x, y, i, (t_vector2){rx - 1, ry});
	else if (y % 64 == 0 && ry > 0 && g_g.maze[rx][ry - 1] == 2)
		ft_calc_sprite(x, y, i, (t_vector2){rx, ry - 1});
	else if (x % 64 == 0 && y % 64 == 0 && rx > 0 && ry > 0 &&
	g_g.maze[rx - 1][ry - 1] == 2)
		ft_calc_sprite(x, y, i, (t_vector2){rx - 1, ry - 1});
	return (1);
}
