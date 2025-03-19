/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_translate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:52 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/02 12:30:44 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	move_it(t_map ***map, t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->x_cpy += vars->right_left;
			map[y][x]->y_cpy += vars->top_down;
			x++;
		}
		y++;
	}
}

void	translate(t_vars *vars, int key)
{
	vars->top_down = 0;
	vars->right_left = 0;
	max_and_min(vars, vars->map, -1, -1);
	if (key == TO_RIGHT && vars->x_min < HEIGHT)
		vars->right_left = vars->translate_var;
	else if (key == TO_LEFT && vars->x_max > 0)
		vars->right_left = -(vars->translate_var);
	else if (key == TO_TOP && vars->y_max > 0)
		vars->top_down = -(vars->translate_var);
	else if (key == TO_DOWN && vars->y_min < WEIDTH)
		vars->top_down = vars->translate_var;
	if (key == TRANSLATE)
	{
		if (vars->translate_var < 40)
			vars->translate_var += 10;
		else
			vars->translate_var = 10;
	}
	move_it(vars->map, vars);
}

static void	zoom_it(t_map ***map, t_vars *vars, int y, int who)
{
	int	x;

	get_first_map(map);
	if (vars->parallel == 1)
	{
		vars->angle_x = 0;
		vars->angle_z = 0;
		vars->angle_y = 0;
	}
	else
		isometric(vars);
	if (who == 1)
		vars->zoom_alpha += 0.1;
	else
		vars->zoom_alpha -= 0.1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x_cpy *= vars->zoom_alpha;
			map[y][x]->y_cpy *= vars->zoom_alpha;
		}
	}
	center_map(map, vars);
}

void	zoom(t_vars *vars, int key)
{
	max_and_min(vars, vars->map, -1, -1);
	vars->x0_center = (vars->x_max + vars->x_min) / 2;
	vars->y0_center = (vars->y_max + vars->y_min) / 2;
	if (key == ZM_OUT && vars->zoom_alpha > 0.2)
	{
		zoom_it(vars->map, vars, -1, 2);
		return_to_its_place(vars->map, vars);
		vars->z_value = 0;
	}
	else if (key == ZM_IN && vars->zoom_alpha < 5)
	{
		zoom_it(vars->map, vars, -1, 1);
		return_to_its_place(vars->map, vars);
		vars->z_value = 0;
	}
}
