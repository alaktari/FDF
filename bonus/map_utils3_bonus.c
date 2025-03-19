/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:41:58 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/01 11:34:03 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	guide_5(char *str, t_vars *vars)
{
	put_str(vars, 5, 446, "go to the main map:  R");
	put_str(vars, 5, 448, "                     _");
	put_str(vars, 5, 461, "----------------------------");
	free(str);
}

static void	guide_4(char *str, t_vars *vars)
{
	if (vars->color == 1)
		put_str(vars, 85, 311, "[Active]");
	else
		put_str(vars, 85, 311, "[Not Active]");
	put_str(vars, 5, 334, "change color:  C");
	put_str(vars, 5, 336, "               _");
	put_str(vars, 2, 349, "----------------------------");
	put_str(vars, 5, 366, "Edit Z:");
	put_str(vars, 5, 367, "______");
	put_str(vars, 5, 368, "______");
	put_str(vars, 5, 390, "change Z:      and    ");
	put_str(vars, 68, 387, "__         __");
	put_str(vars, 68, 388, "__         __");
	put_str(vars, 68, 389, "__         __");
	put_str(vars, 136, 387, "_");
	put_str(vars, 136, 388, "_");
	put_str(vars, 136, 389, "_");
	put_str(vars, 70, 393, "|");
	put_str(vars, 71, 393, "|");
	put_str(vars, 72, 393, "|");
	put_str(vars, 2, 405, "----------------------------");
	put_str(vars, 5, 422, "Return:");
	put_str(vars, 5, 423, "______");
	put_str(vars, 5, 424, "______");
	guide_5(str, vars);
}

static void	guide_3(char *str, t_vars *vars)
{
	put_str(vars, 130, 185, str);
	put_str(vars, 5, 206, "Rotate (X): 8 and 2    ");
	put_str(vars, 77, 208, "_     _");
	ft_itoa((vars->angle_x * 180 / M_PI), str);
	put_str(vars, 130, 207, str);
	put_str(vars, 5, 228, "Rotate (Y): 4 and 6");
	put_str(vars, 77, 230, "_     _");
	ft_itoa((vars->angle_y * 180 / M_PI), str);
	put_str(vars, 130, 229, str);
	put_str(vars, 2, 241, "----------------------------");
	put_str(vars, 5, 256, "Projection:");
	put_str(vars, 5, 257, "__________");
	put_str(vars, 5, 258, "__________");
	put_str(vars, 5, 280, "Parallel: P");
	put_str(vars, 65, 282, "_");
	if (vars->parallel == 1)
		put_str(vars, 80, 281, " [Active]");
	else
		put_str(vars, 85, 281, "[Not Active]");
	put_str(vars, 2, 293, "----------------------------");
	put_str(vars, 5, 310, "Color:");
	put_str(vars, 5, 311, "_____");
	put_str(vars, 5, 312, "_____");
	guide_4(str, vars);
}

static void	guide_2(char *str, t_vars *vars)
{
	put_str(vars, 5, 110, "to right:     || to left:  ");
	put_str(vars, 70, 110, ">");
	put_str(vars, 70, 111, ">");
	put_str(vars, 70, 105, "_");
	put_str(vars, 67, 105, "_");
	put_str(vars, 70, 106, "_");
	put_str(vars, 67, 106, "_");
	put_str(vars, 160, 112, "<");
	put_str(vars, 160, 113, "<");
	put_str(vars, 162, 107, "_");
	put_str(vars, 165, 107, "_");
	put_str(vars, 162, 108, "_");
	put_str(vars, 165, 108, "_");
	put_str(vars, 5, 132, "translate x2: T");
	ft_itoa(vars->translate_var, str);
	put_str(vars, 120, 132, str);
	put_str(vars, 89, 134, "_");
	put_str(vars, 2, 145, "----------------------------");
	put_str(vars, 5, 160, "Rotation: ");
	put_str(vars, 5, 161, "________");
	put_str(vars, 5, 162, "________");
	put_str(vars, 5, 184, "Rotate (Z): 9 and 1    ");
	put_str(vars, 77, 186, "_     _");
	ft_itoa((vars->angle_z * 180 / M_PI), str);
	guide_3(str, vars);
}

int	add_guide(t_vars *vars)
{
	char	*str;

	str = malloc(sizeof(char) * 7);
	if (!str)
		return (close_win(vars), 0);
	put_str(vars, 5, 13, "Zoom: ");
	put_str(vars, 5, 14, "____");
	put_str(vars, 5, 15, "____");
	put_str(vars, 5, 37, "zoom in : I || zoom out: O");
	put_str(vars, 65, 39, "_              _");
	put_str(vars, 2, 50, "----------------------------");
	put_str(vars, 5, 65, "Translate: ");
	put_str(vars, 5, 66, "_________");
	put_str(vars, 5, 67, "_________");
	put_str(vars, 5, 88, "to top:       || to down: ");
	put_str(vars, 57, 89, "^");
	put_str(vars, 58, 89, "^");
	put_str(vars, 57, 89, "|");
	put_str(vars, 58, 89, "|");
	put_str(vars, 160, 89, "|");
	put_str(vars, 161, 90, "|");
	put_str(vars, 162, 89, "|");
	put_str(vars, 161, 91, "v");
	guide_2(str, vars);
	return (1);
}
