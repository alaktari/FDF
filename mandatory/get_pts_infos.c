/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pts_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:49 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/02 15:58:08 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	hex_to_int(char *color, long long result, int power, int i)
{
	while (color[i + 1])
		i++;
	while (i >= 2)
	{
		if (color[i] >= '0' && color[i] <= '9')
			result += (color[i] - 48) * pow(16, power);
		else if (color[i] == 'A')
			result += 10 * pow(16, power);
		else if (color[i] == 'B')
			result += 11 * pow(16, power);
		else if (color[i] == 'C')
			result += 12 * pow(16, power);
		else if (color[i] == 'D')
			result += 13 * pow(16, power);
		else if (color[i] == 'E')
			result += 14 * pow(16, power);
		else if (color[i] == 'F')
			result += 15 * pow(16, power);
		if (result > INT_MAX)
			return (-1);
		power++;
		i--;
	}
	return ((int)result);
}

static int	get_color(char *line, int start, t_list *list)
{
	char	*color;
	int		color_int;
	int		i;
	int		len;

	i = start;
	len = 0;
	while (line[i] && line[i] != ' ' && line[i++] != '\n')
		len++;
	color = malloc(sizeof(char) * len + 1);
	if (!color)
		return (0);
	i = 0;
	while (line[start] && line[start] != ' ' && line[start] != '\n')
	{
		color[i] = line[start];
		i++;
		start++;
	}
	color[i] = '\0';
	color_int = hex_to_int(color, 0, 0, 0);
	if (color_int == -1)
		return (free(color), 0);
	list -> color = color_int;
	return (free(color), 1);
}

static int	the_color(char *line, int index, t_list *list)
{
	size_t	color;

	color = 0;
	if (line[index] == ',' && line[index + 2] != 'x')
	{
		index += 1;
		while (line[index] && line[index] != ' ' && line[index] != '\n')
		{
			color = color * 10 + (line[index] - 48);
			if (color > INT_MAX)
				return (write(2, "Invalide map!!\n", 15), 0);
			index++;
		}
		list -> color = (int)color;
	}
	else if (line[index++] == ',')
	{
		if (!get_color(line, index, list))
			return (write(2, "Invalide map!!\n", 15), 0);
		return (1);
	}
	else
		list -> color = 16777215;
	return (1);
}

int	get_points_infos(char *line, int start, int end, t_list *list)
{
	size_t	result;
	int		sign;

	result = 0;
	sign = 1;
	if (line[start] == '-' || line[start] == '+')
	{
		if (line[start++] == '-')
			sign = -1;
	}
	while (start <= end)
	{
		result = result * 10 + (line[start++] - 48);
		if (result > 159999999)
			return (write(2, "Invalide map!!\n", 15), 0);
		if (line[start] == ',' || line[start] == ' '
			|| line[start] == '\0' || line[start] == '\n')
		{
			if (!the_color(line, start, list))
				return (0);
			list -> z = (int)result * sign;
			return (1);
		}
	}
	return (1);
}
