/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:42 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/16 12:59:50 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;
	size_t	x;

	x = ft_strlen(s1);
	s2 = malloc(sizeof(char) * x + 1);
	if (!(s2))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcln;

	i = 0;
	srcln = ft_strlen(src);
	if (dstsize < 1)
		return (srcln);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcln);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dln;
	size_t	sln;
	size_t	x;

	i = 0;
	x = ft_strlen(dst);
	dln = x;
	sln = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dln)
		return (sln + dstsize);
	while (src[i] != '\0' && i < dstsize - dln - 1)
	{
		dst[x] = src[i];
		i++;
		x++;
	}
	dst[x] = '\0';
	return (dln + sln);
}

char	*ft_strchr(char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	ptr = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			ptr = &s[i];
			return (ptr);
		}
		i++;
	}
	if (s[i] == (char)c)
		ptr = &s[i];
	return (ptr);
}
