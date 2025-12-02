/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:15:30 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/02 09:34:50 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_map(int keysym, t_fractol *fractol);
void	arrow_keys(int keysym, t_range *range, t_axes *shift);
int		close_program(t_fractol *mlx);
int		mouse_scroll(int button, int x, int y, t_fractol *fractol);

void	event_manager(t_fractol *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_map, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_scroll, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, close_program, mlx);
}

int	key_map(int keysym, t_fractol *fractol)
{
	t_axes	shift;

	if (keysym == XK_Escape)
		close_program(fractol);
	shift.x = (fractol->range.max.r - fractol->range.min.r) * 0.05;
	shift.y = (fractol->range.max.i - fractol->range.min.i) * 0.05;
	if (keysym == XK_Left || keysym == XK_Right
		|| keysym == XK_Up || keysym == XK_Down)
		arrow_keys(keysym, &fractol->range, &shift);
	fractol_render(fractol);
	return (0);
}

void	arrow_keys(int keysym, t_range *range, t_axes *shift)
{
	if (keysym == XK_Left)
	{
		range->min.r -= shift->x;
		range->max.r -= shift->x;
	}
	if (keysym == XK_Right)
	{
		range->min.r += shift->x;
		range->max.r += shift->x;
	}
	if (keysym == XK_Up)
	{
		range->min.i += shift->y;
		range->max.i += shift->y;
	}
	if (keysym == XK_Down)
	{
		range->min.i -= shift->y;
		range->max.i -= shift->y;
	}
}

int	close_program(t_fractol *mlx)
{
	mlx_destroy_image(mlx->connection, mlx->img.layer);
	mlx_destroy_window(mlx->connection, mlx->win);
	mlx_destroy_display(mlx->connection);
	free(mlx->connection);
	exit(1);
}

int	mouse_scroll(int button, int x, int y, t_fractol *plan)
{
	t_complex	cursor;

	if (button == 4)
		plan->zoom = 0.99;
	if (button == 5)
		plan->zoom = 1.01;
	cursor.r = plan->range.min.r + (x * plan->coordinates.r);
	cursor.i = plan->range.max.i + (y * plan->coordinates.i);
	plan->range.min.r = cursor.r + (plan->range.min.r - cursor.r) * plan->zoom;
	plan->range.max.r = cursor.r + (plan->range.max.r - cursor.r) * plan->zoom;
	plan->range.min.i = cursor.i + (plan->range.min.i - cursor.i) * plan->zoom;
	plan->range.max.i = cursor.i + (plan->range.max.i - cursor.i) * plan->zoom;
	fractol_render(plan);
	return (0);
}
