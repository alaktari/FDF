/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:40 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/31 15:28:12 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	max_and_min(t_vars *vars, t_map ***map, int y, int x)
{
	vars->x_max = map[0][0]->x_cpy;
	vars->x_min = map[0][0]->x_cpy;
	vars->y_max = map[0][0]->y_cpy;
	vars->y_min = map[0][0]->y_cpy;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (vars->x_max < map[y][x]->x_cpy)
				vars->x_max = map[y][x]->x_cpy;
			if (vars->x_min > map[y][x]->x_cpy)
				vars->x_min = map[y][x]->x_cpy;
			if (vars->y_max < map[y][x]->y_cpy)
				vars->y_max = map[y][x]->y_cpy;
			if (vars->y_min > map[y][x]->y_cpy)
				vars->y_min = map[y][x]->y_cpy;
		}
	}
}

void	get_first_map(t_map ***map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->x_cpy = map[y][x]->x;
			map[y][x]->y_cpy = map[y][x]->y;
			map[y][x]->z_cpy = map[y][x]->z;
			x++;
		}
		y++;
	}
}

void	fill(t_vars *vars)
{
	int		y;
	int		x;

	y = 0;
	while (y <= WEIDTH)
	{
		x = 0;
		while (x <= HEIGHT)
		{
			my_mlx_pixel_put(&(vars->img), x, y, 0);
			x++;
		}
		y++;
	}
}

static void	get_new_color(t_map ***map, t_z_infos *z_infos)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->temp_color = map[y][x]->color;
			if (map[y][x]->z <= 0)
				map[y][x]->color = 0x0000FF;
			else if (map[y][x]->z <= z_infos->range_1)
				map[y][x]->color = 0x00FF00;
			else if (map[y][x]->z <= z_infos->range_2)
				map[y][x]->color = 0xFF0000;
			else
				map[y][x]->color = 0xFFFFFF;
		}
	}
}

void	ft_new_color(t_map ***map, t_z_infos *z_infos)
{
	int	y;
	int	x;
	int	z_max;

	z_max = map[0][0]->z;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (z_max < map[y][x]->z)
				z_max = map[y][x]->z;
		}
	}
	z_infos->range_1 = z_max / 3;
	z_infos->range_2 = z_max - (z_max / 3);
	z_infos->range_3 = z_max;
	get_new_color(map, z_infos);
}
