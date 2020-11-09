/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:42:52 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 21:36:44 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(void *heap)
{
	if (heap != NULL)
		free(heap);
}

void	ft_free_maze(void)
{
	int i;

	if (g_g.maze)
	{
		i = 0;
		while (i < g_g.maze_size.x)
		{
			ft_free(g_g.maze[i]);
			i++;
		}
		ft_free(g_g.maze);
	}
}

void	ft_delspritefree(void)
{
	t_list *lst;
	t_list *tmp;

	if (g_sprites)
	{
		lst = g_sprites;
		while (lst)
		{
			tmp = lst->next;
			free(lst->content);
			lst = tmp;
		}
		ft_free(g_sprites);
		g_sprites = NULL;
	}
}

int		s(float f)
{
	if (f < 0.0f)
		return (-1);
	return (1);
}
