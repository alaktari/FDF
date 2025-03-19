/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:43 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:55:45 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= HEIGHT || y >= WEIDTH || x <= 0 || y <= 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

static void	ft_draw(t_data *img, t_bresenham bresen,
						t_draw_line draw, t_trgb *trgb)
{
	while ((draw.x0) != (draw.x1) || (draw.y0) != (draw.y1))
	{
		my_mlx_pixel_put(img, (draw.x0), (draw.y0), trgb->next_color);
		bresen.check = bresen.diff;
		if (bresen.check > -(bresen.dy))
		{
			bresen.diff -= bresen.dy;
			(draw.x0) += bresen.sx;
		}
		if (bresen.check < bresen.dx)
		{
			bresen.diff += bresen.dx;
			(draw.y0) += bresen.sy;
		}
		get_next_color(trgb);
	}
	my_mlx_pixel_put(img, (draw.x0), (draw.y0), trgb->next_color);
}

static void	drawline(t_data *img, t_draw_line draw)
{
	t_bresenham	bresen;
	t_trgb		trgb;

	get_trgb(draw, &trgb);
	bresen.dx = (draw.x1) - (draw.x0);
	bresen.dy = (draw.y1) - (draw.y0);
	bresen.sx = 0;
	bresen.sy = 0;
	if (bresen.dx > 0)
		bresen.sx = 1;
	else if (bresen.dx < 0)
		bresen.sx = -1;
	if (bresen.dy > 0)
		bresen.sy = 1;
	else if (bresen.dy < 0)
		bresen.sy = -1;
	bresen.dx = abs(bresen.dx);
	bresen.dy = abs(bresen.dy);
	bresen.diff = bresen.dx - bresen.dy;
	ft_draw(img, bresen, draw, &trgb);
}

static void	helper(t_map *map, t_draw_line *draw, int who, t_vars *vars)
{
	int	counter;

	if (!who)
	{
		draw->x0 = map->x_cpy;
		draw->y0 = map->y_cpy;
		draw->color0 = map->color;
	}
	else if (who == 1)
	{
		draw->x1 = map->x_cpy;
		draw->y1 = map->y_cpy;
		draw->color1 = map->color;
	}
	else if (who == 3)
	{
		if (vars->start == 0)
		{
			counter = 0;
			while (counter++ < vars->loop)
				mlx_do_sync(vars->mlx);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
		}
	}
}

void	put_pixels(t_map ***map, t_data *img, t_vars *vars, int y)
{
	int			x;
	t_draw_line	draw;

	draw.pix_space = vars->pix_space;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			helper(map[y][x], &draw, 0, vars);
			if (map[y][x + 1])
			{
				helper(map[y][x + 1], &draw, 1, vars);
				drawline(img, draw);
			}
			if (map[y + 1] && isvalid(map[y + 1], x))
			{
				helper(map[y + 1][x], &draw, 1, vars);
				drawline(img, draw);
			}
			else
				my_mlx_pixel_put(img, draw.x0, draw.y0, draw.color0);
		}
		helper(map[0][0], &draw, 3, vars);
	}
}
