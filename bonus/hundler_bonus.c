/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:34 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/02 15:54:59 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_win(t_vars *vars)
{
	free_map(vars->map, vars->lines - 1);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}

static void	return_and_parallel(t_map ***map, t_vars *vars, int key)
{
	get_first_map(vars->map);
	vars->z_value = 0;
	vars->zoom_alpha = 1;
	if (key == PARALLEL)
	{
		center_map(map, vars);
		vars->angle_x = 0;
		vars->angle_y = 0;
		vars->angle_z = 0;
		vars->parallel = 1;
	}
	else
	{
		vars->parallel = 0;
		vars->angle_x = 0.6108;
		vars->angle_z = 0.6108;
		vars->angle_y = -0.6108;
		rotation(vars->map, vars, 0);
	}
	if (vars->color == 1)
		get_original_color(map);
	vars->color = 0;
}

static void	change_z(t_map ***map, t_vars *vars, int key, int y)
{
	int	x;

	if (vars->parallel == 0 && ((vars->z_value >= -10 && key == M_Z)
			|| (vars->z_value <= 10 && key == P_Z)))
	{
		if (key == P_Z)
			vars->z_value += 0.1;
		else
			vars->z_value -= 0.1;
		get_first_map(map);
		vars->angle_x = 0.6108;
		vars->angle_z = 0.6108;
		vars->angle_y = -0.6108;
		rotation(vars->map, vars, 0);
		while (map[++y])
		{
			x = -1;
			while (map[y][++x])
				map[y][x]->y_cpy -= (map[y][x]->z * vars->z_value);
		}
		center_map(map, vars);
		vars->zoom_alpha = 1;
	}
}

static void	change_color(t_map ***map, t_vars *vars)
{
	t_z_infos	z_infos;

	if (vars->color == 0)
	{
		ft_new_color(map, &z_infos);
		vars->color = 1;
	}
}

int	hundle_hooks(int key, t_vars *vars)
{
	if (key == ESC)
		close_win(vars);
	if (key == TO_TOP || key == TO_DOWN || key == TO_RIGHT
		|| key == TO_LEFT || key == TRANSLATE)
		translate(vars, key);
	if (key == ZM_IN || key == ZM_OUT)
		zoom(vars, key);
	if (key == X_TOP || key == X_DOWN || key == Y_RIGHT
		|| key == Y_LEFT || key == Z_RIGHT || key == Z_LEFT)
	{
		max_and_min(vars, vars->map, -1, -1);
		get_first_map(vars->map);
		rotation(vars->map, vars, key);
	}
	if (key == RETURN || (key == PARALLEL && vars->parallel == 0))
		return_and_parallel(vars->map, vars, key);
	if (key == P_Z || key == M_Z)
		change_z(vars->map, vars, key, -1);
	if (key == COLOR)
		change_color(vars->map, vars);
	fill(vars);
	put_pixels(vars->map, &(vars->img), vars, -1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	add_guide(vars);
	return (0);
}
