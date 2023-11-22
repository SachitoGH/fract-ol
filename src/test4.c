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
	int		max_it;
}	t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int map_color(int var)
{
    // Map the variable to an RGB value based on the range 0 to 20
    int r = 255 - (var * 255) / 20;
    int g = 255 - (var * 255) / 20;
    int b = 255 - (var * 255) / 20;

    // Create the RGB color code
    return (r << 16) | (g << 8) | b;
}

int fractal(t_vars *vars) 
{
	float left = -1.75; 
    float top = -0.25; 
    float xside = 0.25; 
    float yside = 0.45; 
    float xscale, yscale, zx, zy, cx, tempx, cy; 
    int x, y;
    int maxx, maxy, count; 
  
    // getting maximum value of x-axis of screen 
    maxx = 800;
  
    // getting maximum value of y-axis of screen 
    maxy = 800;
  
    // setting up the xscale and yscale 
    xscale = xside / maxx; 
    yscale = yside / maxy; 

  
    // scanning every point in that rectangular area. 
    // Each point represents a Complex number (x + yi). 
    // Iterate that complex number 
    for (y = 1; y <= maxy - 1; y++) { 
        for (x = 1; x <= maxx - 1; x++) 
        { 
            // c_real 
            cx = x * xscale + left; 
  
            // c_imaginary 
            cy = y * yscale + top; 
  
            // z_real 
            zx = 0; 
  
            // z_imaginary 
            zy = 0; 
            count = 0; 
  
            // Calculate whether c(c_real + c_imaginary) belongs 
            // to the Mandelbrot set or not and draw a pixel 
            // at coordinates (x, y) accordingly 
            // If you reach the Maximum number of iterations 
            // and If the distance from the origin is 
            // greater than 2 exit the loop 
            while ((zx * zx + zy * zy < 4) && (count < 20)) 
            { 
                // Calculate Mandelbrot function 
                // z = z*z + c where z is a complex number 
  
                // tempx = z_real*_real - z_imaginary*z_imaginary + c_real 
                tempx = zx * zx - zy * zy + cx; 
  
                // 2*z_real*z_imaginary + c_imaginary 
                zy = 2 * zx * zy + cy; 
  
                // Updating z_real = tempx 
                zx = tempx; 
  
                // Increment count 
                count = count + 1; 
            } 
  
            // To display the created fractal 
            my_mlx_pixel_put(vars, x, y, map_color(count)); 
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
        } 
    }
	return (0);
} 



// int render_next_frame(t_vars *vars)
// {
// 	vars->img = mlx_new_image(vars->mlx, 800, 800);
// 	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, 
// 			&vars->line_length, &vars->endian);
//     my_mlx_pixel_put(vars, vars->x, vars->y, 0x87CEEBFF);
//     mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
//     return (0);
// }

int	main(void)
{
	t_vars	vars;

	vars.max_it = 20;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 800, "Hello world!");
	vars.img = mlx_new_image(vars.mlx, 800, 800);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, 
			&vars.line_length, &vars.endian);

	mlx_loop_hook(vars.mlx, fractal, &vars);
	mlx_loop(vars.mlx);
}