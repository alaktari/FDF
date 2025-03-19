/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:44 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/16 13:49:54 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_join;
	size_t	x;

	x = ft_strlen(s1) + ft_strlen(s2) + 1;
	str_join = malloc(sizeof(char) * x);
	if (!str_join)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(str_join, s1, ft_strlen(s1) + 1);
	ft_strlcat(str_join, s2, x);
	free(s1);
	return (str_join);
}

char	*get_all_line(int fd, char *buffer)
{
	char	*read_bytes;
	ssize_t	i;

	read_bytes = malloc(BUFFER_SIZE + 1);
	if (!read_bytes)
	{
		free(buffer);
		return (NULL);
	}
	i = 1;
	while (!(ft_strchr(buffer, '\n')))
	{
		i = read(fd, read_bytes, BUFFER_SIZE);
		if (i <= 0)
		{
			free(read_bytes);
			if (i == 0)
				return (buffer);
			free(buffer);
			return (NULL);
		}
		read_bytes[i] = '\0';
		buffer = ft_strjoin(buffer, read_bytes);
	}
	return (free(read_bytes), buffer);
}

char	*get_line_to_return(char *buffer)
{
	char	*return_line;
	int		i;
	int		x;

	x = -1;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		return_line = malloc(sizeof(char) * i + 2);
		if (return_line == NULL)
			return (NULL);
		return_line[i + 1] = '\0';
		while (++x <= i)
			return_line[x] = buffer[x];
		return (return_line);
	}
	return_line = malloc(sizeof(char) * i + 1);
	if (!return_line)
		return (NULL);
	while (++x <= i)
		return_line[x] = buffer[x];
	return (return_line);
}

char	*save_other_bytes(char *buffer)
{
	char	*saver;
	int		i;

	saver = NULL;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\0' || (buffer[i] == '\n' && buffer[i + 1] == '\0'))
	{
		free(buffer);
		return (NULL);
	}
	i++;
	saver = ft_strjoin(saver, (buffer + i));
	free(buffer);
	return (saver);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = get_all_line(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	next_line = get_line_to_return(buffer);
	if (next_line == NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	buffer = save_other_bytes(buffer);
	return (next_line);
}
