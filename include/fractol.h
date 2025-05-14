/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:18:45 by ssenas-y          #+#    #+#             */
/*   Updated: 2023/11/23 18:46:50 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_move
{
	double	x;
	double	y;
	double	zoom;
}	t_move;

typedef struct s_vars 
{
	void		*mlx;
	void		*win;
	int			def;
	int			julia;
	int			ship;
	t_move		move;
	t_data		data;
	t_complex	seed;
	double		color;
}	t_vars;

int		verif(int argc, char *argv[]);
double	ft_atof(const char *str);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	scale(double number, double new_min, double new_max, double old_max);
int		fractal(t_complex c, t_vars *vars);
int		render_next_frame(t_vars *vars);
int		finish(t_vars *vars);
int		key_event(int keycode, t_vars *vars);
int		mouse_event(int keycode, int x, int y, void *param);
void	set_julia(t_vars *vars, char *argv[]);
void	set_vars(t_vars *vars, char *argv[]);

#endif
