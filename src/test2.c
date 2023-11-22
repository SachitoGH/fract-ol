#include <mlx.h>
#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3

typedef struct s_vars {
    void    *mlx;
    void    *win;
    void    *img;
	void	*prev_img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     x;
    int     y;
    int     move_up;
    int     move_down;
    int     move_left;
    int     move_right;
} t_vars;

void my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
    char    *dst;

    dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void update_position(t_vars *vars)
{
    if (vars->move_up)
        vars->y -= 1;
    if (vars->move_down)
        vars->y += 1;
    if (vars->move_left)
        vars->x -= 1;
    if (vars->move_right)
        vars->x += 1;
}


int render_next_frame(t_vars *vars)
{
    mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars->img);

    if (vars->move_up)
        vars->y -= 1;
    if (vars->move_down)
        vars->y += 1;
    if (vars->move_left)
        vars->x -= 1;
    if (vars->move_right)
        vars->x += 1;

    my_mlx_pixel_put(vars, vars->x, vars->y, 0x87CEEBFF);

    mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, vars->win);

    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

    return (0);
}


int key_press(int keycode, t_vars *vars)
{
    if (keycode == 13) // W key
        vars->move_up = 1;
    else if (keycode == 0) // A key
        vars->move_left = 1;
    else if (keycode == 1) // S key
        vars->move_down = 1;
    else if (keycode == 2) // D key
        vars->move_right = 1;

    return (0);
}

int key_release(int keycode, t_vars *vars)
{
    if (keycode == 13) // W key
        vars->move_up = 0;
    else if (keycode == 0) // A key
        vars->move_left = 0;
    else if (keycode == 1) // S key
        vars->move_down = 0;
    else if (keycode == 2) // D key
        vars->move_right = 0;

    return (0);
}

int main(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.x = 100;
    vars.y = 100;
    vars.move_up = 0;
    vars.move_down = 0;
    vars.move_left = 0;
    vars.move_right = 0;

    vars.win = mlx_new_window(vars.mlx, 800, 800, "Hello world!");

    mlx_loop_hook(vars.mlx, render_next_frame, &vars);
    mlx_hook(vars.win, 2, 1L << 0, key_press, &vars); // KeyPress event
    mlx_hook(vars.win, 3, 1L << 1, key_release, &vars); // KeyRelease event
    mlx_loop(vars.mlx);

    return (0);
}
