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

int	key_event(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		finish(vars);
	}
	if (keycode == 12 && vars->color > 0)
		vars->color -= 5;
	if (keycode == 14 && vars->color < 100)
		vars->color += 5;
	if (keycode == 126 || keycode == 13)
		vars->move.y -= 0.2 * vars->move.zoom;
	if (keycode == 123 || keycode == 0)
		vars->move.x -= 0.2 * vars->move.zoom;
	if (keycode == 125 || keycode == 1)
		vars->move.y += 0.2 * vars->move.zoom;
	if (keycode == 124 || keycode == 2)
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
