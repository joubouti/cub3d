/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:58:53 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 20:16:02 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_image(void)
{
	g_g.img.ptr = mlx_new_image(g_g.mlx_ptr, g_g.win_w, g_g.win_h);
	g_g.img.w = g_g.win_w;
	g_g.img.h = g_g.win_h;
	g_g.img.data = mlx_get_data_addr(g_g.img.ptr, &g_g.img.bpp, &g_g.img.sl,
	&g_g.img.endian);
}

void	ft_draw_maze(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_g.maze_size.x)
	{
		j = 0;
		while (j < g_g.maze_size.y)
		{
			if (g_g.maze[i][j] == 1)
				ft_draw_rectangle(&g_g.img, (t_vector2){i * 64, j * 64},
				(t_vector2){64, 64}, 0x0000FF00);
			else if (g_g.maze[i][j] == 2)
				ft_draw_rectangle(&g_g.img, (t_vector2){i * 64, j * 64},
				(t_vector2){64, 64}, 0x0000FFFF);
			j++;
		}
		i++;
	}
}

void	ft_raycast(t_sprite *sp)
{
	int			i;
	float		a;
	t_vector3	hit;
	t_vector2	p;
	t_list		*lst;

	i = 0;
	while (i < g_g.win_w)
	{
		a = (g_g.rot - g_g.fov * ((float)i / (float)g_g.win_w - 0.5f)) * g_dg;
		p.x = g_g.pos.x + g_g.cam_dis * sin(a);
		p.y = g_g.pos.y + g_g.cam_dis * cos(a);
		hit = ft_draw_ray((t_vector3){g_g.pos.x, g_g.pos.y, i}, p);
		ft_check_ray(i, hit, a);
		lst = g_sprites;
		while (lst)
		{
			if ((sp = lst->content) && sp->i == i)
				ft_draw_sprite(lst->content);
			lst = lst->next;
		}
		i++;
	}
	ft_delspritefree();
}

int		ft_draw(void)
{
	ft_init_image();
	ft_draw_rectangle(&g_g.img, (t_vector2){0, 0}, (t_vector2){g_g.win_w,
	g_g.win_h / 2}, g_tx.f);
	ft_draw_rectangle(&g_g.img, (t_vector2){0, g_g.win_h / 2},
	(t_vector2){g_g.win_w, g_g.win_h / 2}, g_tx.c);
	ft_raycast(NULL);
	ft_keyhold();
	mlx_put_image_to_window(g_g.mlx_ptr, g_g.win_ptr, g_g.img.ptr, 0, 0);
	if (g_save == 1)
	{
		ft_bitmap(0, 0, 0, 0);
		ft_close();
	}
	mlx_destroy_image(g_g.mlx_ptr, g_g.img.ptr);
	return (0);
}
