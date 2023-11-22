#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


int	mouse_move_hook(int x, int y, t_vars *vars)
{
    int width = 800;
    int height = 800;

    (void)vars;
    if (x >= 0 && x <= width && y >= 0 && y <= height)
	    printf("x = %d, y = %d\n", x, y);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	closer(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int click(int keycode, t_vars *vars)
{
    (void)vars;
    (void)keycode;
    if (keycode == 1)
        printf("click\n");
    return (0);
}

int printer(int keycode, t_vars *vars)
{
    (void)vars;
    printf("Key: %d\n", keycode);
    return (0);
}

int render_next_frame(void *param)
{
    t_data *img = (t_data *)param;
    static int i = 1;

    img.img = mlx_new_image(vars.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
	&img.line_length, &img.endian);
    if (i < 800)
    {
        my_mlx_pixel_put(img, i, i, 0x87CEEBFF);
        i++;
        mlx_put_image_to_window(vars.mlx, vars.win, img->img, 0, 0);
    }
    else
        i = 1;
    return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	// int		i;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 800, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
			&img.line_length, &img.endian);

    // Draw a square
    // int color[5];

    // color[0] = 0x00008BFF;
    // color[1] = 0x0000FFFF;
    // color[2] = 0x00FFFFFF;
    // color[3] = 0xADD8E6FF;
    // color[4] = 0x87CEEBFF;

	// int x = 100;
    // int y = 100;
    // int side_length = 200;
    // int i = x;
    // int j = 0;
    // int k = 0;

    // while (i < x + side_length)
    // {
    //     j = y;
    //     while (j < y + side_length)
    //     {
    //         if (k > 4)
    //             k = 0;
    //         my_mlx_pixel_put(&img, i, j, color[j % 4]);
    //         j++;
    //         k++;
    //     }
    //     i++;
    // }

	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

    // Quit when press ESC
    // mlx_hook(vars.win, 2, 0, closer, &vars);
    // mlx_key_hook(vars.win, printer, &vars);
    // mlx_hook(vars.win, 6, 1L<<4, mouse_move_hook, &vars);
	// mlx_mouse_hook(vars.win, click, &vars);
    mlx_loop_hook(vars.mlx, render_next_frame, (void *)&vars);
	mlx_loop(vars.mlx);
}
