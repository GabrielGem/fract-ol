/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:15:30 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/27 10:00:33 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	event_manager(t_fractol *fractol)
{
	mlx_hook(fractol->mlx_win, KeyPress, KeyPressMask, key_map, fractol);
	mlx_hook(fractol->mlx_win, DestroyNotify, StructureNotifyMask, close_program, fractol);
	mlx_hook(fractol->mlx_win, ButtonPress, ButtonPressMask, mouse_scroll, fractol);
}

int	key_map(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		close_program(fractol);
	if (keysym == XK_Left)
		fractol->axis.x += (1 * fractol->zoom);
	if (keysym == XK_Right)
		fractol->axis.x -= (1 * fractol->zoom);
	if (keysym == XK_Up)
		fractol->axis.y += (1 * fractol->zoom);
	if (keysym == XK_Down)
		fractol->axis.y -= (1 * fractol->zoom);
	fractol_render(fractol);
	return (0);
}

int	close_program(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.layer);
	mlx_destroy_window(fractol->mlx, fractol->mlx_win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(1);
}

int	mouse_scroll(int button, int x, int y, t_fractol *fractol)
{
	t_complex	real_position;

	real_position.r = (((2.0 - (-2.0)) / WIDTH) * x) + (-2.0);
	real_position.i = (((-2.0 - 2.0) / HEIGHT) * y) + 2.0;
	printf("x: %f, y: %f\n", real_position.r, real_position.i);
	printf("button: %d\n", button);
	fractol_render(fractol);
	return (0);
}
