/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:38:47 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/23 15:57:22 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char g_header[54] = { 0 };

void	ft_bitmap_create(unsigned char *buf, uint32_t imagesize)
{
	int				fd;

	fd = open("screenshot.bmp", O_WRONLY | O_CREAT);
	if (fd == -1)
		return ;
	write(fd, g_header, 54);
	write(fd, buf, imagesize);
	close(fd);
	free(buf);
}

void	ft_bitmap_calc(uint32_t imagesize, int32_t width, int32_t height,
int width_in_bytes)
{
	unsigned char	*buf;
	int				row;
	int				col;
	int				i;

	row = height - 1;
	buf = malloc(imagesize);
	while (row >= 0)
	{
		col = 0;
		while (col < width)
		{
			i = col * 4 + g_g.img.sl * (height - 1 - row);
			buf[row * width_in_bytes + col * 3 + 0] = g_g.img.data[i];
			buf[row * width_in_bytes + col * 3 + 1] = g_g.img.data[i + 1];
			buf[row * width_in_bytes + col * 3 + 2] = g_g.img.data[i + 2];
			col++;
		}
		row--;
	}
	ft_bitmap_create(buf, imagesize);
}

void	ft_bitmap(int32_t width, int32_t height, uint16_t bitcount,
int width_in_bytes)
{
	uint32_t			imagesize;
	const uint32_t		bisize = 40;
	const uint32_t		bfoffbits = 54;
	uint32_t			filesize;
	const uint16_t		biplanes = 1;

	width = g_g.img.w;
	height = g_g.img.h;
	bitcount = 24;
	width_in_bytes = ((width * bitcount + 31) / 32) * 4;
	imagesize = width_in_bytes * height;
	filesize = 54 + imagesize;
	ft_memcpy(g_header, "BM", 2);
	ft_memcpy(g_header + 2, &filesize, 4);
	ft_memcpy(g_header + 10, &bfoffbits, 4);
	ft_memcpy(g_header + 14, &bisize, 4);
	ft_memcpy(g_header + 18, &width, 4);
	ft_memcpy(g_header + 22, &height, 4);
	ft_memcpy(g_header + 26, &biplanes, 2);
	ft_memcpy(g_header + 28, &bitcount, 2);
	ft_memcpy(g_header + 34, &imagesize, 4);
	ft_bitmap_calc(imagesize, width, height, width_in_bytes);
}
