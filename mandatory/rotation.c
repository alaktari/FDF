/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:24:09 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/24 21:34:03 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z(int *x, int *y, t_vars *vars)
{
	int		new_x;
	int		new_y;

	new_x = *x * cos(vars->angle_z) - *y * sin(vars->angle_z);
	new_y = *x * sin(vars->angle_z) + *y * cos(vars->angle_z);
	*y = new_y;
	*x = new_x;
}

static void	rotate_x(int *z, int *y, t_vars *vars)
{
	int		new_z;
	int		new_y;

	new_y = *y * cos(vars->angle_x) - *z * sin(vars->angle_x);
	new_z = *y * sin(vars->angle_x) + *z * cos(vars->angle_x);
	*y = new_y;
	*z = new_z;
}

static void	rotate_y(int *x, int *z, t_vars *vars)
{
	int		new_x;
	int		new_z;

	new_x = *x * cos(vars->angle_y) + *z * sin(vars->angle_y);
	new_z = -*x * sin(vars->angle_y) + *z * cos(vars->angle_y);
	*x = new_x;
	*z = new_z;
}

void	rotation(t_map ***map, t_vars *vars)
{
	int		y;
	int		x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			rotate_x(&(map[y][x]->z), &(map[y][x]->y), vars);
			rotate_y(&(map[y][x]->x), &(map[y][x]->z), vars);
			rotate_z(&(map[y][x]->x), &(map[y][x]->y), vars);
		}
	}
}
