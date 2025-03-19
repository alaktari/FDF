/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:56:33 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 16:01:17 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>

# define HEIGHT 1800
# define WEIDTH 900

typedef struct s_map
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_map;

typedef struct s_list
{
	int				z;
	unsigned int	color;
	struct s_list	*next;
}	t_list;

typedef struct s_win_infos
{
	void	*mlx;
	void	*mlx_win;
	int		pix_space;
	int		x_max;
	int		x_min;
	int		y_max;
	int		y_min;
}	t_win_infos;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	diff;
	int	check;
}	t_bresenham;

typedef struct s_draw_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	pix_space;
	int	color0;
	int	color1;
	int	color_per;
}	t_draw_line;

typedef struct s_trgb
{
	float	t0;
	float	r0;
	float	g0;
	float	b0;
	float	t1;
	float	r1;
	float	g1;
	float	b1;
	float	t_perce;
	float	r_perce;
	float	g_perce;
	float	b_perce;
	int		next_color;
}	t_trgb;

typedef struct s_vars
{
	int			lines;
	float		var;
	int			pix_space;
	int			x_max;
	int			x_min;
	int			y_max;
	int			y_min;
	void		*mlx;
	void		*win;
	t_map		***map;
	t_data		img;
	t_win_infos	wiin;
	float		angle_x;
	float		angle_y;
	float		angle_z;
}	t_vars;

char	*get_next_line(int fd);
int		check_and_fix(char **strs, int i, int x, int len);
int		get_points_infos(char *line, int start, int end, t_list *list);
void	free_strs(char **strs);
void	free_linked_list(t_list *head);
t_list	*get_list(char *line, int *len, int i, int start_index);
void	free_map(t_map ***map, int alloced);
int		get_the_map(char *file, int lines, t_map ***map, int i);
int		the_lines(t_map ***map);
int		ft_count_lines(char *file, int *lines,
			ssize_t read_bytes, char last_char);
int		ft_max_row(t_map ***map);
void	fill(t_vars *vars);
void	put_pixels(t_data *img, t_vars *vars, int y, int x);
void	get_trgb(t_draw_line draw, t_trgb *trgb);
void	get_next_color(t_trgb *trgb);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		isvalid(t_map **map, int x);
void	center_map(t_map ***map, t_vars *vars);
int		close_win1(t_vars *vars);
int		close_win2(int keycode, t_vars *vars);
void	rotation(t_map ***map, t_vars *vars);

#endif
