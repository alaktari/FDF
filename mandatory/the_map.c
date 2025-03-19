/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:54 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 16:00:42 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_lines(char *file, int *lines,
		ssize_t read_bytes, char last_char)
{
	int		fd;
	char	buffer[1025];
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Invalid file!!\n", 14), 0);
	while (read_bytes)
	{
		read_bytes = read(fd, buffer, 1024);
		if (read_bytes < 0)
			return (close(fd), 0);
		buffer[read_bytes] = '\0';
		i = -1;
		while (buffer[++i] != '\0')
		{
			if (buffer[i] == '\n')
				(*lines)++;
			last_char = buffer[i];
		}
	}
	if (last_char != '\n')
		(*lines)++;
	return (close(fd), 1);
}

static char	**read_file(char *file, int lines, int i)
{
	char	**strs;
	int		fd;

	while (file[i])
		i++;
	if (file[--i] != 'f' || file[--i] != 'd' || file[--i] != 'f'
		|| file[--i] != '.')
		return (write(2, "Invalid file!!\n", 14), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = -1;
	strs = malloc(sizeof(char *) * (lines + 1));
	if (!strs)
		return (NULL);
	strs[lines] = NULL;
	while (++i < lines)
	{
		strs[i] = get_next_line(fd);
		if (!strs[i])
			return (write(2, "Invalide map!!\n", 15), free_strs(strs), NULL);
	}
	if (!check_and_fix(strs, -1, 0, 0))
		return (free_strs(strs), NULL);
	return (strs);
}

static void	put_in_map(t_map ***map, t_list *list, int i)
{
	int		x;
	t_list	*head;

	x = 0;
	head = list;
	while (list)
	{
		map[i][x]->z = list->z;
		map[i][x]->color = list->color;
		list = list->next;
		x++;
	}
	free_linked_list(head);
}

static int	allocation_for_points(t_map ***map, int i, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		map[i][x] = malloc(sizeof(t_map));
		if (!map[i][x])
			return (free_map(map, i), 0);
		x++;
	}
	map[i][len] = NULL;
	return (1);
}

int	get_the_map(char *file, int lines, t_map ***map, int i)
{
	char	**strs;
	t_list	*list;
	int		len;

	len = 0;
	strs = read_file(file, lines, 0);
	if (!strs)
		return (free(map), 0);
	while (++i < lines)
	{
		list = get_list(strs[i], &len, 0, 0);
		if (!list)
			return (free_strs(strs), free_map(map, (i - 1)), 0);
		if (len < 2 && i == 0)
			return (write(2, "Invalide map!!\n", 15), free_linked_list(list),
				free_strs(strs), free_map(map, (i - 1)), 0);
		map[i] = malloc(sizeof(t_map *) * (len + 1));
		if (!map[i])
			return (free_strs(strs), free_linked_list(list),
				free_map(map, (i - 1)), 0);
		if (!allocation_for_points(map, i, len))
			return (free_strs(strs), free_linked_list(list), 0);
		put_in_map(map, list, i);
	}
	return (free_strs(strs), 1);
}
