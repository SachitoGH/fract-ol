/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:08:25 by ssenas-y          #+#    #+#             */
/*   Updated: 2023/11/23 17:20:32 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	finish(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	verif(int argc, char *argv[])
{
	if ((argc != 3 || ft_strncmp(argv[1], "mandelbrot", 10) || 
			ft_atof(argv[2]) > 100 || ft_atof(argv[2]) < 1)
		&& (argc != 3 || ft_strncmp(argv[1], "ship", 4) || 
			ft_atof(argv[2]) > 100 || ft_atof(argv[2]) < 1) 
		&& (argc != 5 || ft_strncmp(argv[1], "julia", 5) || 
			ft_atof(argv[4]) > 100 || ft_atof(argv[4]) < 1))
	{
		ft_printf("\t\033[0;31m[Usage]\033[0m\n");
		ft_printf("\033[0;33mMandelbrot:\033[0m\t./fractol mandelbrot");
		ft_printf(" <step 1-100>\n");
		ft_printf("\033[0;33mJulia:\033[0m\t\t");
		ft_printf("./fractol  julia <real number> <imaginary number>");
		ft_printf(" <step 1-100>\n");
		ft_printf("\033[0;33mBurning ship:\033[0m\t./fractol ship");
		ft_printf(" <step 1-100>\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;

	if (verif(argc, argv))
		exit(1);
	set_vars(&vars, argv);
	mlx_key_hook(vars.win, key_event, &vars);
	mlx_mouse_hook(vars.win, mouse_event, &vars);
	mlx_hook(vars.win, 17, 0, finish, &vars);
	render_next_frame(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
