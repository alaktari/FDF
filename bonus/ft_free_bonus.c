/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:19 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/24 19:03:48 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_linked_list(t_list *head)
{
	t_list	*next;

	while (head)
	{
		next = head -> next;
		free(head);
		head = next;
	}
}

void	free_map(t_map ***map, int alloced)
{
	int	i;
	int	x;

	i = 0;
	while (i <= alloced)
	{
		x = 0;
		while (map[i][x])
		{
			free(map[i][x]);
			x++;
		}
		free(map[i]);
		i++;
	}
	free(map);
}
