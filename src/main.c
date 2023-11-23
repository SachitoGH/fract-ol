#include "fractol.h"

int finish(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;

	if ((argc != 2 || ft_strncmp(argv[1], "Mandelbrot", 10)) && (argc != 4 || ft_strncmp(argv[1], "Julia", 5)))
	{
		printf("\t\033[0;31m[Usage]\033[0m\n"); // TODO import printf
		printf("\033[0;33mMandelbrot:\033[0m\t./fractol Mandelbrot\n");
		printf("\033[0;33mJulia:\033[0m\t\t./fractol  Julia <real number> <imaginary number>\n");
		exit(1);
	}
	set_vars(&vars, argv);
	mlx_key_hook(vars.win, key_event, &vars);
	mlx_mouse_hook(vars.win, mouse_event, &vars);
	mlx_hook(vars.win, 17, 0, finish, &vars);
	render_next_frame(&vars);
	mlx_loop(vars.mlx);
	return (0);
}