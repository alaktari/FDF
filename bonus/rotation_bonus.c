/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/02 09:49:11 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

static void	ft_set_vars(t_vars *vars, int key)
{
	if (key == X_TOP)
		vars->angle_x += 0.0872;
	else if (key == X_DOWN)
		vars->angle_x -= 0.0872;
	else if (key == Y_LEFT)
		vars->angle_y += 0.0872;
	else if (key == Y_RIGHT)
		vars->angle_y -= 0.0872;
	else if (key == Z_RIGHT)
		vars->angle_z += 0.0872;
	else if (key == Z_LEFT)
		vars->angle_z -= 0.0872;
	if (vars->angle_x >= 6.3656 || vars->angle_x <= -6.3)
		vars->angle_x = 0;
	if (vars->angle_y >= 6.3656 || vars->angle_y <= -6.3)
		vars->angle_y = 0;
	if (vars->angle_z >= 6.3656 || vars->angle_z <= -6.3)
		vars->angle_z = 0;
	if (key != 0)
		vars->z_value = 0;
}

void	rotation(t_map ***map, t_vars *vars, int key)
{
	int		y;
	int		x;

	vars->x0_center = (vars->x_max + vars->x_min) / 2;
	vars->y0_center = (vars->y_max + vars->y_min) / 2;
	ft_set_vars(vars, key);
	if (key != 0)
		vars->zoom_alpha = 1;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x_cpy = map[y][x]->x;
			map[y][x]->y_cpy = map[y][x]->y;
			rotate_x(&(map[y][x]->z_cpy), &(map[y][x]->y_cpy), vars);
			rotate_y(&(map[y][x]->x_cpy), &(map[y][x]->z_cpy), vars);
			rotate_z(&(map[y][x]->x_cpy), &(map[y][x]->y_cpy), vars);
		}
	}
	center_map(vars->map, vars);
}
