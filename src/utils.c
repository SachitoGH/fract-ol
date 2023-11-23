/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:08:35 by ssenas-y          #+#    #+#             */
/*   Updated: 2023/11/23 18:46:21 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}

void	set_julia(t_vars *vars, char *argv[])
{
	vars->julia = 1;
	vars->seed.real = ft_atof(argv[2]);
	vars->seed.i = ft_atof(argv[3]);
	vars->def = ft_atof(argv[4]);
}

void	set_vars(t_vars *vars, char *argv[])
{
	vars->mlx = mlx_init();
	vars->move.x = 0;
	vars->move.y = 0;
	vars->move.zoom = 1;
	vars->data.img = mlx_new_image(vars->mlx, 800, 800);
	vars->data.addr = mlx_get_data_addr(vars->data.img, 
			&vars->data.bits_per_pixel, 
			&vars->data.line_length, &vars->data.endian);
	vars->win = mlx_new_window(vars->mlx, 800, 800, "FRACTAL!");
	vars->color = 0;
	if (!ft_strncmp(argv[1], "ship", 4))
		vars->ship = 1;
	else
		vars->ship = 0;
	if (!ft_strncmp(argv[1], "julia", 5))
		set_julia(vars, argv);
	else
	{
		vars->julia = 0;
		vars->def = ft_atof(argv[2]);
	}
}

double	ft_atof_fraction(const char *str, int i)
{
	double	fraction;
	double	pow;

	pow = 1;
	fraction = 0;
	if (str[i] == '.')
		i++;
	fraction = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		pow /= 10;
		fraction += (str[i] - '0') * pow;
		i++;
	}
	return (fraction);
}

double	ft_atof(const char *str)
{
	double	nbr;
	double	tmp;
	int		i;
	double	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '.' && str[i] >= '0' && str[i] <= '9')
	{
		tmp = nbr;
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr < tmp)
			return (-(sign == 1));
		i++;
	}
	return ((nbr + ft_atof_fraction(str, i)) * sign);
}
