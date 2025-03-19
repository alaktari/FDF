/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_fix_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:01:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/05/26 15:31:08 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	check_color(char *s, int i)
{
	if ((s[i] == '0' && s[i + 1] == 'x')
		&& (s[i + 2] != '\0' && s[i + 2] != ' ' && s[i + 2] != '\n'))
	{
		i += 2;
		while (s[i] && s[i] != '\n' && s[i] != ' ')
		{
			if (((s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A'
						&& s[i] <= 'F')) || (s[i] >= '0' && s[i] <= '9'))
				i++;
			else
				return (0);
		}
	}
	else if (s[i] >= '0' && s[i] <= '9')
	{
		while (s[i] && s[i] != '\n' && s[i] != ' ')
		{
			if (s[i] < '0' || s[i] > '9')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (i);
}

static int	check_the_line(char *s, int i)
{
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			if (s[i] == ' ' || s[i] == '-' || s[i] == '+' || s[i] == '\n')
			{
				if (s[i] == '+' || s[i] == '-')
				{
					if ((s[i + 1] < '0' || s[i + 1] > '9')
						|| (i && s[i - 1] != ' '))
						return (0);
				}
			}
			else if (s[i] == ',')
			{
				i = check_color(s, (i + 1));
				if (!i)
					return (0);
				continue ;
			}
			else
				return (0);
		}
	}
	return (1);
}

static void	ft_cpy(char *line, char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
}

static int	parse_the_lines(char *line, int len, int i, int x)
{
	char	*temp;

	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	temp[len] = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 0 || line[i--] == '\n')
		return (free(temp), 0);
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			if (line[i] >= 'a' && line[i] <= 'f')
				temp[x++] = line[i] - 32;
			else
				temp[x++] = line[i];
		}
		else if (line[i] == ' ' && line[i + 1] != ' '
			&& line[i + 1] && line[i + 1] != '\n')
			temp[x++] = ' ';
	}
	temp[x] = '\0';
	return (ft_cpy(line, temp), free(temp), 1);
}

int	check_and_fix(char **strs, int i, int x, int len)
{
	while (strs[++i])
	{
		len = 0;
		x = 0;
		if (!check_the_line(strs[i], -1))
		{
			write(2, "Invalide map!!\n", 15);
			return (0);
		}
		while (strs[i][x])
		{
			len++;
			x++;
		}
		if (!parse_the_lines(strs[i], len, 0, 0))
		{
			write(2, "Invalide map!!\n", 15);
			return (0);
		}
	}
	return (1);
}
