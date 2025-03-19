/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:50 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:52:06 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	get_next_color(t_trgb *trgb)
{
	if (trgb->t0 < trgb->t1)
		trgb->t0 += trgb->t_perce;
	else if (trgb->t0 > trgb->t1)
		trgb->t0 -= trgb->t_perce;
	if (trgb->r0 < trgb->r1)
		trgb->r0 += trgb->r_perce;
	else if (trgb->r0 > trgb->r1)
		trgb->r0 -= trgb->r_perce;
	if (trgb->g0 < trgb->g1)
		trgb->g0 += trgb->g_perce;
	else if (trgb->g0 > trgb->g1)
		trgb->g0 -= trgb->g_perce;
	if (trgb->b0 < trgb->b1)
		trgb->b0 += trgb->b_perce;
	else if (trgb->b0 > trgb->b1)
		trgb->b0 -= trgb->b_perce;
	trgb->next_color = create_trgb((int)trgb->t0, (int)trgb->r0,
			(int)trgb->g0, (int)trgb->b0);
}

void	get_trgb(t_draw_line draw, t_trgb *trgb)
{
	float	diff;

	trgb->t0 = get_t(draw.color0);
	trgb->r0 = get_r(draw.color0);
	trgb->g0 = get_g(draw.color0);
	trgb->b0 = get_b(draw.color0);
	trgb->t1 = get_t(draw.color1);
	trgb->r1 = get_r(draw.color1);
	trgb->g1 = get_g(draw.color1);
	trgb->b1 = get_b(draw.color1);
	diff = fabs(trgb->t0 - trgb->t1);
	trgb->t_perce = diff / draw.pix_space;
	diff = fabs(trgb->r0 - trgb->r1);
	trgb->r_perce = diff / draw.pix_space;
	diff = fabs(trgb->g0 - trgb->g1);
	trgb->g_perce = diff / draw.pix_space;
	diff = fabs(trgb->b0 - trgb->b1);
	trgb->b_perce = diff / draw.pix_space;
	trgb->next_color = draw.color0;
}

void	get_original_color(t_map ***map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			map[y][x]->color = map[y][x]->temp_color;
	}
}
