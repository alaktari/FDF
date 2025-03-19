/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:30 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:45:45 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_isometric(t_map ***map, t_vars *vars)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x = x * vars->pix_space;
			map[y][x]->y = y * vars->pix_space;
		}
	}
	vars->angle_x = 0.6108;
	vars->angle_z = 0.6108;
	vars->angle_y = -0.6108;
	rotation(vars->map, vars);
	center_map(vars->map, vars);
}

static int	window_img_data(t_vars *vars, t_data *img, t_map ***map)
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
	vars->map = map;
	vars->img = *img;
	return (1);
}

static int	get_window(t_map ***map, t_vars *vars, t_data *img)
{
	int	taller;
	int	smaller;
	int	max_row;

	if (!window_img_data(vars, img, map))
		return (0);
	vars->lines = the_lines(map);
	max_row = ft_max_row(map);
	taller = fmax(max_row, vars->lines);
	smaller = fmin(max_row, vars->lines);
	if (smaller > 300)
		vars->var = 0.7;
	else if (smaller > 180 || smaller < 50)
		vars->var = 0.5;
	else
		vars->var = 0.6;
	vars->pix_space = HEIGHT / taller * vars->var;
	get_isometric(vars->map, vars);
	put_pixels(img, vars, -1, -1);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	mlx_hook(vars->win, 2, 1L << 0, close_win2, vars);
	mlx_hook(vars->win, 17, 1L << 2, close_win1, vars);
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
