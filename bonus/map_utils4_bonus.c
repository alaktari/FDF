/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils4_bonus.c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:28:01 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/04 21:28:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_str(t_vars *vars, int x, int y, char *str)
{
	mlx_string_put(vars->mlx, vars->win, x, y, 0XFFFFFF, str);
}

void	return_to_its_place(t_map ***map, t_vars *vars)
{
	int	y;
	int	x;
	int	x_add;
	int	y_add;

	max_and_min(vars, vars->map, -1, -1);
	vars->x1_center = (vars->x_max + vars->x_min) / 2;
	vars->y1_center = (vars->y_max + vars->y_min) / 2;
	x_add = vars->x0_center - vars->x1_center;
	y_add = vars->y0_center - vars->y1_center;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			map[y][x]->x_cpy += x_add;
			map[y][x]->y_cpy += y_add;
		}
	}
}

static size_t	digits_len(int n)
{
	size_t	the_len;

	the_len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
		the_len++;
	while (n != 0)
	{
		n = n / 10;
		the_len++;
	}
	return (the_len);
}

static void	ft_itoa_2(char *my_itoa, int n, int x, int i)
{
	while (x-- > i)
	{
		if (n < 0)
			my_itoa[x] = '0' + (n % 10) * (-1);
		else
			my_itoa[x] = '0' + (n % 10);
		n = n / 10;
	}
}

void	ft_itoa(int n, char *my_itoa)
{
	size_t	i;
	size_t	x;

	if (((n % 5) != 0) && (n > 0))
		n += 1;
	else if (((n % 5) != 0) && (n < 0))
		n -= 1;
	i = 1;
	x = digits_len(n) + 3;
	my_itoa[0] = '[';
	my_itoa[x - 2] = ']';
	my_itoa[x - 1] = '\0';
	if (n < 0)
	{
		my_itoa[1] = '-';
		i = 2;
	}
	x -= 2;
	ft_itoa_2(my_itoa, n, x, i);
}
