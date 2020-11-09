/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:47:45 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 21:36:50 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# define WINW 1024
# define WINH 768

typedef struct		s_vector2
{
	float x;
	float y;
}					t_vector2;

typedef struct		s_vector3
{
	float x;
	float y;
	float z;
}					t_vector3;

typedef struct		s_vector4
{
	float x;
	float y;
	float w;
	float h;
}					t_vector4;

typedef struct		s_image
{
	void	*ptr;
	char	*data;
	int		w;
	int		h;
	int		bpp;
	int		sl;
	int		endian;
}					t_image;

typedef struct		s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;

}					t_texture;

typedef struct		s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_w;
	int			win_h;
	t_image		img;
	t_image		tex[4];
	int			cam_dis;
	float		rot;
	int			fov;
	t_vector2	pos;
	char		**maze;
	t_vector2	maze_size;
	float		speed;

}					t_cub3d;

typedef struct		s_sprite
{
	t_vector2	z;
	t_vector2	pos;
	int			i;
	float		offset;
	float		d;
}					t_sprite;

extern	t_cub3d		g_g;
extern const float	g_dg;
extern t_texture	g_tx;
extern t_list		*g_sprites;
extern char			g_save;

void				ft_draw_texture(t_image *img_ptr, t_vector3 p, int offset,
int face);
t_vector3			ft_draw_ray(t_vector3 p0, t_vector2 p1);
void				ft_camera_plane(t_vector2 p0, t_vector2 p1);
int					ft_getpixel(t_image *img_ptr, int x, int y);
int					ft_error(int n, int err);
void				ft_maze(char *file);
int					ft_create_maze(char *line, int fd);
void				ft_bitmap(int32_t a, int32_t b, uint16_t c, int d);
int					ft_draw(void);
void				ft_draw_rectangle(t_image *img_ptr, t_vector2 p,
t_vector2 s, int color);
void				ft_draw_grid(t_image *img_ptr);
void				ft_setpixel(t_image *img_ptr, int x, int y, int color);
int					ft_getpixel(t_image *img_ptr, int x, int y);
void				ft_free_maze();
int					ft_keypress(int keycode);
int					ft_keyrelease(int keycode);
void				ft_keyhold(void);
int					ft_close(void);
int					ft_check_rayhit(int x, int y, int i);
void				ft_check_ray(float i, t_vector3 hit, float a);
void				ft_loadtextures(void);
int					ft_check_sprite(int x, int y, int i);
void				ft_sorted_list_insert(t_list **begin_list, void *content,
int (*cmp)());
int					ft_cmp(t_sprite *s1, t_sprite *s2);
t_sprite			*ft_newsprite(t_vector2 z, t_vector2 pos, int i,
t_vector2 m);
int					ft_draw_sprite(t_sprite *sp);
void				ft_delspritefree();
int					ft_isin(int x, int y);
int					ft_sprite_rendered(t_vector2 r, int i);
int					s(float f);

#endif
