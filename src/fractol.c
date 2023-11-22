#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

typedef struct s_vars 
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	x;
	double	y;
	double	zoom;
	int		def;
	int		julia;
	double	jr;
	double	ji;
}	t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
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

double scale(double number, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (number - old_min) / (old_max - old_min) + new_min;
}

int	fractal(t_complex c, t_vars *vars)
{
	t_complex	z;
	double 		tmp;
	int			i;

	z.real = 0;
	z.i = 0;
	if (vars->julia == 1)
	{
		z.real = vars->jr;
		z.i = vars->ji;
	}
	i = 0;
	while (i < vars->def)
	{
		tmp = (z.real * z.real) - (z.i * z.i) + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = tmp;
		if (((z.real * z.real) + (z.i * z.i)) > 4)
		{
			return (scale(i, 0x000000, 0xFFFFFF, 0, vars->def));
		}
		i++;
	}
	return (scale(i, 0x000000, 0xFFFFFF, 0, vars->def));
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
			c.real = (scale(i, -2, 1, 0, 799) * vars->zoom) + vars->x;
			c.i = (scale(j, -1.5, 1.5, 0, 799) * vars->zoom) + vars->y;
			my_mlx_pixel_put(vars, i, j, fractal(c, vars));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	mousepress(int keycode, int x, int y, void *param)
{
	t_vars	*vars;
	(void)x;
	(void)y;
	vars = (t_vars *)param;
	if (keycode == 4)
		vars->zoom *= 1.05;
	if (keycode == 5)
		vars->zoom *= 0.95;
	return (0);
}

int finish(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(0);
}
int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		finish(vars);
	}
	if (keycode == 126 || keycode == 13)
		vars->y -= 0.2 * vars->zoom;
	if (keycode == 123 || keycode == 0)
		vars->x -= 0.2 * vars->zoom;
	if (keycode == 125 || keycode == 1)
		vars->y += 0.2 * vars->zoom;
	if (keycode == 124 || keycode == 2)
		vars->x += 0.2 * vars->zoom;
	return (0);
}
void set_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->x = 0;
	vars->y = 0;
	vars->zoom = 1;
	vars->img = mlx_new_image(vars->mlx, 800, 800);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, 
			&vars->line_length, &vars->endian);
	vars->win = mlx_new_window(vars->mlx, 800, 800, "FRACTAL!");
	vars->def = 50;
	vars->julia = 0;
}
void set_julia(t_vars *vars, char *argv[])
{
	vars->julia = 1;
	vars->jr = atof(argv[2]); // TODO atof
	vars->ji = atof(argv[3]);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;

	if ((argc != 2 || ft_strncmp(argv[1], "Mandelbrot", 10)) && (argc != 4 || ft_strncmp(argv[1], "Julia", 5)))
	{
		printf("[Usage]\nMandelbrot: ./fractol Mandelbrot\nJulia:      ./fractol Julia <real number> <imaginary number>\n"); // TODO import printf
		exit(1);
	}
	set_vars(&vars);
	mlx_key_hook(vars.win, keypress, &vars);
	mlx_mouse_hook(vars.win, mousepress, &vars);
	mlx_hook(vars.win, 17, 0, finish, &vars);
    if (argc == 4)
		set_julia(&vars, argv);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}