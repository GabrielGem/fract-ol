/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/27 11:06:32 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		return (0);
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
	{
		fractol.name_win = argv[1];
		fractol_init(&fractol);
		fractol_render(&fractol);
		mlx_loop(fractol.mlx);
	}
	return (0);
}

void	fractol_init(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	fractol->mlx_win = mlx_new_window(
			fractol->mlx, WIDTH, HEIGHT, fractol->name_win);
	fractol->img.layer = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.addr = mlx_get_data_addr(fractol->img.layer, &fractol->img.bpp,
			&fractol->img.line_len, &fractol->img.endian);
	fractol->range = (t_range){.min = (t_complex){.r = -2.0, .i = -2.0},
			.max = (t_complex){.r = 2.0, .i = 2.0}};
	fractol->coordinates.r = (fractol->range.max.r - (fractol->range.min.r)) / WIDTH;
	fractol->coordinates.i = (fractol->range.min.i - fractol->range.max.i) / HEIGHT;
	fractol->axis = (t_axes){.x = 0.0, .y = 0.0};
	fractol->zoom = 1.0;
	event_manager(fractol);
}

void	fractol_render(t_fractol *fractol)
{
	int			x;
	int			y;
	int			*pixel_ptr;
	int			out;

	pixel_ptr = (int *)fractol->img.addr;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			out = handle_pixel(x, y, fractol);
			if (out == ITERATIONS)
				*pixel_ptr = BLACK;
			else
				*pixel_ptr = (out * 2) << 16 | (out * 4) << 8 | (out * 8);
			pixel_ptr++;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win,
		fractol->img.layer, 0, 0);
}

int	handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z = (t_complex){.r = 0.0, .i = 0.0};
	c.r = (fractol->range.min.r + (x * fractol->coordinates.r) * fractol->zoom) + fractol->axis.x;
	c.i = (fractol->range.max.i + (y * fractol->coordinates.i) * fractol->zoom) + fractol->axis.y;
	i = 0;
	while (i < ITERATIONS)
	{
		if ((z.r * z.r) + (z.i * z.i) > 4.0)
			return (i);
		z = (t_complex){.r = (((z.r * z.r) - (z.i * z.i)) + c.r),
			.i = ((2 * z.r * z.i) + c.i)};
		i++;
	}
	return (ITERATIONS);
}
