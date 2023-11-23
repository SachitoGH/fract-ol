/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:08:16 by ssenas-y          #+#    #+#             */
/*   Updated: 2023/11/23 15:26:35 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->data.addr + (y * vars->data.line_length 
			+ x * (vars->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	scale(double number, double new_min, 
		double new_max, double old_max)
{
	return ((new_max - new_min) * (number / old_max) + new_min);
}

int	fractal(t_complex c, t_vars *vars)
{
	t_complex	z;
	double		tmp;
	int			i;

	z.real = c.real;
	z.i = c.i;
	if (vars->julia == 1)
		c = vars->jul;
	i = 0;
	while (i < vars->def)
	{
		tmp = (z.real * z.real) - (z.i * z.i) + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = tmp;
		if (((z.real * z.real) + (z.i * z.i)) > 4)
		{
			return (scale(i + vars->color, 0x000000, 0xFFFFFF, vars->def));
		}
		i++;
	}
	return (scale(i + vars->color, 0x000000, 0xFFFFFF, vars->def));
}

int	render_next_frame(t_vars *vars)
{
	t_complex	c;
	int			i;
	int			j;

	i = 0;
	while (i < 800)
	{
		j = 0;
		while (j < 800)
		{
			c.real = (scale(i, -2, 1, 799) * vars->move.zoom) + vars->move.x;
			c.i = (scale(j, -1.5, 1.5, 799) * vars->move.zoom) 
				+ vars->move.y;
			my_mlx_pixel_put(vars, i, j, fractal(c, vars));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (0);
}
