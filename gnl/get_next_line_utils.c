/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:05:11 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/14 16:26:45 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	slen;
	size_t	i;

	slen = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && i < slen)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (slen);
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*c;

	len = ft_strlen(src);
	c = malloc(len + 1);
	if (!c)
		return (NULL);
	ft_strlcpy(c, src, len + 1);
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*cat;
	int		i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	cat = malloc(len1 + len2 + 1);
	if (!cat)
		return (NULL);
	while (i < len1 + len2)
	{
		if (i < len1)
			cat[i] = s1[i];
		else
			cat[i] = s2[i - len1];
		i++;
	}
	cat[i] = '\0';
	return (cat);
}

char	*ft_strchr(char *str, int c)
{
	size_t i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
