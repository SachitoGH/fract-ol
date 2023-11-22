#include <mlx.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int render_next_frame(t_vars *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, 800, 800);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, 
			&vars->line_length, &vars->endian);
    my_mlx_pixel_put(vars, vars->x, vars->y, 0x87CEEBFF);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
    return (0);
}

int	position(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->y -= 1;
	if (keycode == 0)
		vars->x -= 1;
	if (keycode == 1)
		vars->y += 1;
	if (keycode == 2)
		vars->x += 1;
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.x = 100;
	vars.y = 100;
	
	vars.win = mlx_new_window(vars.mlx, 800, 800, "Hello world!");

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_key_hook(vars.win, position, &vars);
	mlx_loop(vars.mlx);
}