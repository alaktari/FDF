/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:52 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 16:00:16 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		bresen.check = 2 * bresen.diff;
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
		if (draw.color0 > draw.color1)
			get_next_color(trgb);
		else if (draw.color0 < draw.color1)
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

static void	get_first_and_second(t_map *map, t_draw_line *draw, int who)
{
	if (!who)
	{
		draw->x0 = map->x;
		draw->y0 = map->y;
		draw->color0 = map->color;
	}
	else
	{
		draw->x1 = map->x;
		draw->y1 = map->y;
		draw->color1 = map->color;
	}
}

void	put_pixels(t_data *img, t_vars *vars, int y, int x)
{
	t_draw_line	draw;

	draw.pix_space = vars->pix_space;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
		{
			get_first_and_second(vars->map[y][x], &draw, 0);
			if (vars->map[y][x + 1])
			{
				get_first_and_second(vars->map[y][x + 1], &draw, 1);
				drawline(img, draw);
			}
			if (vars->map[y + 1] && isvalid(vars->map[y + 1], x))
			{
				get_first_and_second(vars->map[y + 1][x], &draw, 1);
				drawline(img, draw);
			}
			else
				my_mlx_pixel_put(img, draw.x0, draw.y0, draw.color0);
		}
	}
}
