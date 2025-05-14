/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:08:05 by ssenas-y          #+#    #+#             */
/*   Updated: 2023/11/23 16:42:14 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <X11/keysym.h>

int key_event(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		finish(vars);
	if (keycode == XK_q && vars->color > 0)
		vars->color -= 5;
	if (keycode == XK_e && vars->color < 100)
		vars->color += 5;
	if (keycode == XK_w || keycode == XK_Up)
		vars->move.y -= 0.2 * vars->move.zoom;
	if (keycode == XK_a || keycode == XK_Left)
		vars->move.x -= 0.2 * vars->move.zoom;
	if (keycode == XK_s || keycode == XK_Down)
		vars->move.y += 0.2 * vars->move.zoom;
	if (keycode == XK_d || keycode == XK_Right)
		vars->move.x += 0.2 * vars->move.zoom;
	render_next_frame(vars);
	return (0);
}


int	mouse_event(int keycode, int x, int y, void *param)
{
	t_vars	*vars;

	(void)x;
	(void)y;
	vars = (t_vars *)param;
	if (keycode == 4)
		vars->move.zoom *= 1.05;
	if (keycode == 5)
		vars->move.zoom *= 0.95;
	render_next_frame(vars);
	return (0);
}
