/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:01:33 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:26:12 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	the_lines(t_map ***map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	isvalid(t_map **map, int x)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (i > x)
		return (1);
	return (0);
}

int	ft_max_row(t_map ***map)
{
	int	y;
	int	x;
	int	max_row;

	max_row = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (max_row < x)
			max_row = x;
		y++;
	}
	return (max_row);
}

static void	max_and_min(t_vars *vars, t_map ***map, int y, int x)
{
	vars->x_max = map[0][0]->x;
	vars->x_min = map[0][0]->x;
	vars->y_max = map[0][0]->y;
	vars->y_min = map[0][0]->y;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (vars->x_max < map[y][x]->x)
				vars->x_max = map[y][x]->x;
			if (vars->x_min > map[y][x]->x)
				vars->x_min = map[y][x]->x;
			if (vars->y_max < map[y][x]->y)
				vars->y_max = map[y][x]->y;
			if (vars->y_min > map[y][x]->y)
				vars->y_min = map[y][x]->y;
		}
	}
}

void	center_map(t_map ***map, t_vars *vars)
{
	int	x;
	int	y;
	int	x_map_center;
	int	y_map_center;

	max_and_min(vars, map, -1, -1);
	x_map_center = vars->x_max - ((vars->x_max - vars->x_min) / 2);
	y_map_center = vars->y_max - ((vars->y_max - vars->y_min) / 2);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x += ((HEIGHT) / 2) - x_map_center;
			map[y][x]->y += ((WEIDTH) / 2) - y_map_center;
		}
	}
}
