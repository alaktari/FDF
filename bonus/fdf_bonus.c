/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:13 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:39:44 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	set_vars(t_vars *vars)
{
	vars->translate_var = 10;
	vars->zoom_alpha = 1;
	vars->parallel = 0;
	vars->z_value = 0;
	vars->color = 0;
	vars->start = 0;
}

static void	get_original_map(t_map ***map, t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->x = x * vars->pix_space;
			map[y][x]->y = y * vars->pix_space;
			map[y][x]->x_cpy = map[y][x]->x;
			map[y][x]->y_cpy = map[y][x]->x;
			map[y][x]->z_cpy = map[y][x]->z;
			x++;
		}
		y++;
	}
}

static int	window_img_data(t_vars *vars, t_data *img, t_map ***map,
				t_pix_space *space)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (free(map), 0);
	vars->win = mlx_new_window(vars->mlx, HEIGHT, WEIDTH, "FDF");
	if (!vars->win)
		return (free(map), 0);
	img->img = mlx_new_image(vars->mlx, HEIGHT, WEIDTH);
	if (!img->img)
		return (free(map), 0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (free(map), 0);
	vars->lines = the_lines(map);
	space->max_row = ft_max_row(map);
	space->taller = fmax(space->max_row, vars->lines);
	space->smaller = fmin(space->max_row, vars->lines);
	if (space->smaller > 300)
		vars->var = 0.7;
	else if (space->smaller > 180 || space->smaller < 50)
		vars->var = 0.5;
	else
		vars->var = 0.6;
	return (1);
}

static int	get_window(t_map ***map, t_vars *vars, t_data *img)
{
	t_pix_space	space;

	if (!window_img_data(vars, img, map, &space))
		return (0);
	vars->pix_space = HEIGHT / (space.taller) * vars->var;
	vars->map = map;
	vars->img = *img;
	set_vars(vars);
	get_original_map(map, vars);
	isometric(vars);
	vars->loop = 8000;
	if (vars->lines > 300)
		vars->loop = 900;
	if (vars->lines > 150)
		vars->loop = 1800;
	put_pixels(map, img, vars, -1);
	vars->start = 1;
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	add_guide(vars);
	mlx_hook(vars->win, 2, 1L << 0, hundle_hooks, vars);
	mlx_hook(vars->win, 17, 1L << 2, close_win, vars);
	mlx_loop(vars->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_map	***map;
	t_vars	vars;
	t_data	img;
	int		count_lines;

	count_lines = 0;
	if (ac == 2)
	{
		if (!ft_count_lines(av[1], &count_lines, 1, '\0'))
			return (1);
		map = malloc(sizeof(t_map **) * (count_lines + 1));
		if (!map)
			return (1);
		map[count_lines] = NULL;
		if (count_lines == -1)
			return (1);
		if (!get_the_map(av[1], count_lines, map, -1))
			return (1);
		if (!get_window(map, &vars, &img))
			return (1);
		return (0);
	}
}
