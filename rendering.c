/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:17:06 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/01 14:17:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_pixel(int x, int y, t_fractol *fractol);

void	fractol_render(t_fractol *info)
{
	int	x;
	int	y;
	int	*pixel_ptr;
	int	out;

	pixel_ptr = (int *)info->img.addr;
	info->coordinates.r = (info->range.max.r - (info->range.min.r)) / WIDTH;
	info->coordinates.i = (info->range.min.i - info->range.max.i) / HEIGHT;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			out = handle_pixel(x, y, info);
			if (out == ITERATIONS)
				*pixel_ptr = BLACK;
			else
				*pixel_ptr = (out * 2) << 16 | (out * 4) << 8 | (out * 8);
			pixel_ptr++;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->connection, info->win, info->img.layer, 0, 0);
}

static int	handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	t_complex	pixel;
	double		temp_real;
	int			i;

	pixel.r = fractol->range.min.r + (x * fractol->coordinates.r);
	pixel.i = fractol->range.max.i + (y * fractol->coordinates.i);
	z = (t_complex){0.0, 0.0};
	c = pixel;
	if (fractol->name[0] == 'j')
	{
		z = pixel;
		c = fractol->k;
	}
	i = -1;
	while (++i < ITERATIONS)
	{
		if ((z.r * z.r) + (z.i * z.i) > 4.0)
			return (i);
		temp_real = ((z.r * z.r) - (z.i * z.i)) + c.r;
		z.i = (2 * z.r * z.i) + c.i;
		z.r = temp_real;
	}
	return (ITERATIONS);
}
