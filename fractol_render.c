/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:17:06 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/17 14:07:17 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_pixel(int x, int y, t_fractol *fractol);
static int	get_color_fast(int out, int max_iterations);

void	fractol_render(t_fractol *info)
{
	int	x;
	int	y;
	int	*pixel_ptr;
	int	out;

	pixel_ptr = (int *)info->img.addr;
	info->coordinates.r = (info->range.max.r - (info->range.min.r)) / width;
	info->coordinates.i = (info->range.min.i - info->range.max.i) / height;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			out = handle_pixel(x, y, info);
			*pixel_ptr = get_color_fast(out, iterations);
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
	if (fractol->name[0] == 'J')
	{
		z = pixel;
		c = fractol->k;
	}
	i = -1;
	while (++i < iterations)
	{
		if ((z.r * z.r) + (z.i * z.i) > 4.0)
			return (i);
		temp_real = ((z.r * z.r) - (z.i * z.i)) + c.r;
		z.i = (2 * z.r * z.i) + c.i;
		z.r = temp_real;
	}
	return (iterations);
}

static inline int	get_color_fast(int out, int max_iterations)
{
	t_color	color;

	if (out == max_iterations)
		return (BLACK);
	color.s_channels.r = (unsigned char)(out * 11);
	color.s_channels.g = (unsigned char)(out * 13 + 50);
	color.s_channels.b = (unsigned char)(out * 7 + 100);
	color.s_channels.a = 0;
	return (color.number);
}
