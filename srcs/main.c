/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:40:11 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 17:28:07 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d		g_g;
const float	g_dg = M_PI / 180;
char		g_save = 0;

int		ft_close(void)
{
	ft_free_maze();
	exit(-1);
	return (0);
}

void	ft_init(void)
{
	g_g.mlx_ptr = mlx_init();
	g_g.win_ptr = mlx_new_window(g_g.mlx_ptr, g_g.win_w, g_g.win_h, "Wolf 3d");
	g_g.fov = 66;
	g_g.cam_dis = g_g.win_w;
	g_g.speed = 3;
	ft_loadtextures();
}

int		main(int argc, char *argv[])
{
	if ((argc != 2 && argc != 3) || (argc == 3 && ft_strncmp(argv[2], "--save",
	6)))
		ft_error(-1, 3);
	if (argc == 3)
		g_save = 1;
	ft_maze(argv[1]);
	ft_init();
	mlx_hook(g_g.win_ptr, 17, 0L, ft_close, NULL);
	mlx_hook(g_g.win_ptr, 2, 1L << 0, ft_keypress, NULL);
	mlx_hook(g_g.win_ptr, 3, 1L << 1, ft_keyrelease, NULL);
	mlx_loop_hook(g_g.mlx_ptr, ft_draw, NULL);
	mlx_loop(g_g.mlx_ptr);
	return (0);
}
