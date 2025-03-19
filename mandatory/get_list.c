/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:39 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/16 18:49:10 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*new_list(t_list *list, t_list *head, int *len)
{
	list -> next = malloc(sizeof(t_list));
	if (!(list -> next))
	{
		free_linked_list(head);
		return (NULL);
	}
	list -> next -> next = NULL;
	(*len)++;
	return (list -> next);
}

static int	find_start_index(char *line, int i)
{
	int	start_index;

	start_index = 0;
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-'
			|| line[i] == '+')
		{
			start_index = i;
			break ;
		}
		i++;
	}
	return (start_index);
}

static int	find_end_index(char *line, int i)
{
	int	end_index;

	end_index = 0;
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
			&& (line[i + 1] == ' ' || line[i + 1] == '\n'
				|| line[i + 1] == '\0'))
		{
			end_index = i;
			break ;
		}
		i++;
	}
	return (end_index);
}

t_list	*get_list(char *line, int *len, int i, int start_index)
{
	t_list	*head;
	t_list	*list;
	int		end_index;

	*len = 1;
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	head = list;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
	{
		start_index = find_start_index(line, i);
		end_index = find_end_index(line, start_index);
		i = end_index + 1;
		if (!get_points_infos(line, start_index, end_index, list))
			return (free_linked_list(head), NULL);
		if (line[i] == ' ')
		{
			list = new_list(list, head, len);
			if (!list)
				return (NULL);
			i++;
		}
	}
	return (head);
}
