/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:38 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/02 09:28:06 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	the_lines(t_map ***map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
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

void	center_map(t_map ***map, t_vars *vars)
{
	int	x;
	int	y;
	int	x_map_center;
	int	y_map_center;

	max_and_min(vars, map, -1, -1);
	x_map_center = (vars->x_max + vars->x_min) / 2;
	y_map_center = (vars->y_max + vars->y_min) / 2;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x_cpy += ((HEIGHT) / 2) - x_map_center;
			map[y][x]->y_cpy += ((WEIDTH) / 2) - y_map_center;
		}
	}
}

void	isometric(t_vars *vars)
{
	vars->angle_x = 0.6108;
	vars->angle_z = 0.6108;
	vars->angle_y = -0.6108;
	rotation(vars->map, vars, 0);
}
