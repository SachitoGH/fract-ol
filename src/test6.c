#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>


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
}	t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int map_color(int step, int max)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
    r = 255 - (step * 255) / max;
    // g = 255 - (step * 255) / max;
    b = 255 - (step * 255) / max;

    // Create the RGB color code
    return (r << 16) | (g << 8) | b;
}
double scale(double number, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (number - old_min) / (old_max - old_min) + new_min;
}

int	mandelbrot(t_complex c)
{
	t_complex	z;
	double 		tmp;
	int			i;
	int			max;

	max = 30;
	z.real = 0;
	z.i = 0;
	i = 0;
	while (i < max)
	{
		tmp = (z.real * z.real) - (z.i * z.i) + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = tmp;
		if (((z.real * z.real) + (z.i * z.i)) > 4)
		{
			// printf("no\n");
			return (map_color(i, max));
		}
		// printf("(%f ; %fi)\n", z.real, z.i);
		i++;
	}
	// printf("yes\n");
	return (map_color(max, max));
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
			c.real = scale(i, -2, 1, 0, 799);
			c.i = scale(j, -1.5, 1.5, 0, 799);
			my_mlx_pixel_put(vars, i, j, mandelbrot(c));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
int	finish(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_vars		vars;

	vars.mlx = mlx_init();
	vars.img = mlx_new_image(vars.mlx, 800, 800);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, 
			&vars.line_length, &vars.endian);
	vars.win = mlx_new_window(vars.mlx, 800, 800, "FRACTAL!");
	render_next_frame(&vars);
	mlx_key_hook(vars.win, finish, &vars);
    // mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}