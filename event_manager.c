/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:15:30 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/29 17:32:42 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	event_manager(t_fractol *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_map, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_scroll, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, close_program, mlx);
}

int	key_map(int keysym, t_fractol *fractol)
{
	t_axes	shift;

	shift.x = (fractol->range.max.r - fractol->range.min.r) * 0.05;
	shift.y = (fractol->range.max.i - fractol->range.min.i) * 0.05;
	if (keysym == XK_Escape)
		close_program(fractol);
	if (keysym == XK_Left)
	{
		fractol->range.min.r -= shift.x;
		fractol->range.max.r -= shift.x;
	}
	if (keysym == XK_Right)
	{
		fractol->range.min.r += shift.x;
		fractol->range.max.r += shift.x;
	}
	if (keysym == XK_Up)
	{
		fractol->range.min.i += shift.y;
		fractol->range.max.i += shift.y;
	}
	if (keysym == XK_Down)
	{
		fractol->range.min.i -= shift.y;
		fractol->range.max.i -= shift.y;
	}
	fractol_render(fractol);
	return (0);
}

int	close_program(t_fractol *mlx)
{
	mlx_destroy_image(mlx->connection, mlx->img.layer);
	mlx_destroy_window(mlx->connection, mlx->win);
	mlx_destroy_display(mlx->connection);
	free(mlx->connection);
	exit(1);
}

int	mouse_scroll(int button, int x, int y, t_fractol *fractol)
{
	t_complex	mouse_position;

	if (button == 4)
		fractol->zoom = 0.99;
	if (button == 5)
		fractol->zoom = 1.01;
	mouse_position.r = fractol->range.min.r + (x * fractol->coordinates.r);
	mouse_position.i = fractol->range.max.i + (y * fractol->coordinates.i);
	fractol->range.min.r = mouse_position.r + ((fractol->range.min.r - mouse_position.r) * fractol->zoom);
	fractol->range.max.r = mouse_position.r + ((fractol->range.max.r - mouse_position.r) * fractol->zoom);
	fractol->range.min.i = mouse_position.i + ((fractol->range.min.i - mouse_position.i) * fractol->zoom);
	fractol->range.max.i = mouse_position.i + ((fractol->range.max.i - mouse_position.i) * fractol->zoom);
	fractol_render(fractol);
	return (0);
}
