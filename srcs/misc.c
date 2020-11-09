/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:03:58 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 20:22:23 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sorted_list_insert(t_list **begin_list, void *content,
int (*cmp)())
{
	t_list *p;
	t_list *elem;

	elem = ft_lstnew(content);
	p = *begin_list;
	if (p == NULL || cmp(p->content, content) > 0)
	{
		elem->next = p;
		*begin_list = elem;
	}
	else
	{
		while (p->next && (cmp(p->next->content, content) >= 0))
		{
			p = p->next;
		}
		elem->next = p->next;
		p->next = elem;
	}
}

int			ft_cmp(t_sprite *s1, t_sprite *s2)
{
	return (s1->d > s2->d);
}

t_sprite	*ft_newsprite(t_vector2 z, t_vector2 pos, int i, t_vector2 m)
{
	t_sprite *sp;

	sp = malloc(sizeof(t_sprite));
	sp->z.x = z.x;
	sp->z.y = z.y;
	sp->pos.x = pos.x;
	sp->pos.y = pos.y;
	sp->i = i;
	sp->offset = m.x;
	sp->d = m.y;
	return (sp);
}

int			ft_sprite_rendered(t_vector2 r, int i)
{
	t_list		*lst;
	t_sprite	*s;

	lst = g_sprites;
	while (lst)
	{
		s = lst->content;
		if (s->pos.x == r.x && s->pos.y == r.y && s->i == i)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int			ft_isin(int x, int y)
{
	int rx;
	int ry;

	rx = x / 64;
	ry = y / 64;
	if (g_g.maze[rx][ry])
		return (0);
	else if (x % 64 == 0 && (rx > 0 && g_g.maze[rx - 1][ry]))
		return (0);
	else if (y % 64 == 0 && (ry > 0 && g_g.maze[rx][ry - 1]))
		return (0);
	return (1);
}
