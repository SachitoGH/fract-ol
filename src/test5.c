#include <mlx.h>

typedef struct s_vars {
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

void Mandelbrot(t_vars *vars,int X,int Y,double range[])
{
    int i,j;
    unsigned char k;
    double xmin = range[0];
    double ymin = range[1];
    double xstep = (range[2]-range[0])/X;
    double ystep = (range[3]-range[1])/Y;
    double x,y,z0x,z0y,temp;
    for(i=0;i<X;i++)
        for(j=0;j<Y;j++)
        {
            z0x = xmin + xstep*i;
            z0y = ymin + ystep*j;
            x = 0.0;
            y = 0.0;
            k = 0;
            while((x*x+y*y)<4.0 && k<255)
            {
                temp=x;
                x=x*x-y*y+z0x;
                y=2*temp*y+z0y;
                k++;
            }
            if (k>10 && k<250)
                while(0);
            my_mlx_pixel_put(vars,i,j,k);
        }
}

int main(void)
{
	t_vars vars;
    int X,Y;
	double range[4] = {-1.0,-1.0,1.0,1.0};

	X = Y = 256;
    vars.mlx = mlx_init();
	vars.img = mlx_new_image(vars.mlx, X, Y);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, 
			&vars.line_length, &vars.endian);

	vars.win = mlx_new_window(vars.mlx, X, Y, "Hello world!");
    mlx_loop_hook(vars.mlx, Mandelbrot, &vars);
    
    return 0;
}
