/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:16 by alaktari          #+#    #+#             */
/*   Updated: 2024/06/03 15:57:53 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>

# define HEIGHT 1800
# define WEIDTH 900
# define ESC 65307
# define TO_TOP 65362
# define TO_DOWN 65364
# define TO_RIGHT 65363
# define TO_LEFT 65361
# define X_TOP 65431
# define X_DOWN 65433
# define Y_RIGHT 65432
# define Y_LEFT 65430
# define Z_RIGHT 65434
# define Z_LEFT 65436
# define P_Z 65451
# define M_Z 65453
# define TRANSLATE 116
# define ZM_IN 105
# define ZM_OUT 111
# define RETURN 114
# define PARALLEL 112
# define COLOR 99

typedef struct s_map
{
	int				x;
	int				y;
	int				z;
	int				x_cpy;
	int				y_cpy;
	int				z_cpy;
	unsigned int	color;
	unsigned int	temp_color;
}	t_map;

typedef struct s_list
{
	int				z;
	unsigned int	color;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_pix_space
{
	int	taller;
	int	smaller;
	int	max_row;
}	t_pix_space;

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

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	diff;
	int	check;
}	t_bresenham;

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
	int			pix_space;
	int			max_row;
	float		var;
	int			x_max;
	int			x_min;
	int			y_max;
	int			y_min;
	void		*mlx;
	void		*win;
	t_map		***map;
	t_data		img;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			right_left;
	int			top_down;
	int			translate_var;
	float		zoom_alpha;
	int			parallel;
	float		z_value;
	float		color;
	int			x0_center;
	int			y0_center;
	int			x1_center;
	int			y1_center;
	int			start;
	int			loop;
}	t_vars;

typedef struct s_z_infos
{
	float	range_1;
	float	range_2;
	float	range_3;
}	t_z_infos;

int		ft_count_lines(char *file, int *lines,
			ssize_t read_bytes, char last_char);
char	*get_next_line(int fd);
int		check_and_fix(char **strs, int i, int x, int len);
int		get_points_infos(char *line, int start, int end, t_list *list);
void	free_strs(char **strs);
void	free_linked_list(t_list *head);
t_list	*get_list(char *line, int *len, int i, int start_index);
void	free_map(t_map ***map, int alloced);
int		get_the_map(char *file, int lines, t_map ***map, int i);
int		the_lines(t_map ***map);
int		ft_max_row(t_map ***map);
int		close_win(t_vars *vars);
int		hundle_hooks(int key, t_vars *vars);
void	isometric(t_vars *vars);
void	rotation(t_map ***map, t_vars *vars, int key);
void	center_map(t_map ***map, t_vars *vars);
void	max_and_min(t_vars *vars, t_map ***map, int y, int x);
void	put_pixels(t_map ***map, t_data *img, t_vars *vars, int y);
int		isvalid(t_map **map, int x);
void	get_trgb(t_draw_line draw, t_trgb *trgb);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		create_trgb(int t, int r, int g, int b);
void	get_next_color(t_trgb *trgb);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	translate(t_vars *vars, int key);
void	get_first_map(t_map ***map);
void	zoom(t_vars *vars, int key);
void	fill(t_vars *vars);
void	ft_new_color(t_map ***map, t_z_infos *z_infos);
void	get_original_color(t_map ***map);
void	return_to_its_place(t_map ***map, t_vars *vars);
void	set_zoom(t_map ***map, t_vars *vars);
void	ft_itoa(int n, char *my_itoa);
int		add_guide(t_vars *vars);
void	put_str(t_vars *vars, int x, int y, char *str);

#endif