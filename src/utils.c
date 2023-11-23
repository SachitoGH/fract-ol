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

void set_julia(t_vars *vars, char *argv[])
{
	vars->julia = 1;
	vars->jul.real = atof(argv[2]); // TODO atof
	vars->jul.i = atof(argv[3]);
}
void set_vars(t_vars *vars, char *argv[])
{
	vars->mlx = mlx_init();
	vars->move.x = 0;
	vars->move.y = 0;
	vars->move.zoom = 1;
	vars->data.img = mlx_new_image(vars->mlx, 800, 800);
	vars->data.addr = mlx_get_data_addr(vars->data.img, &vars->data.bits_per_pixel, 
			&vars->data.line_length, &vars->data.endian);
	vars->win = mlx_new_window(vars->mlx, 800, 800, "FRACTAL!");
	vars->def = 50;
	vars->color = 0;
	vars->julia = 0;
	if (!ft_strncmp(argv[1], "Julia", 5))
		set_julia(vars, argv);
}