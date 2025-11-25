/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/25 17:10:37 by gabrgarc         ###   ########.fr       */
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
	fractol->img.addr = mlx_get_data_addr(
			fractol->img.layer, &fractol->img.bpp, &fractol->img.line_len,
			&fractol->img.endian);
}

double	pantograph(double unscaled, double old_max,
		double new_min, double new_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min);
}

void	fractol_render(t_fractol *fractol)
{
	int	x;
	int	y;

	x = 0;
	while (x < HEIGHT)
	{
		y = 0;
		while (y < HEIGHT)
		{
			handle_pixel(x, y, fractol);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win,
				fractol->img.layer, 0, 0);
}

void	handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			iterations;
	int			color;

	z.r = 0.0;
	z.i = 0.0;
	c.r = pantograph(x, WIDTH, -2, +2);
	c.i = pantograph(y, HEIGHT, +2, -2);
	i = 0;
	iterations = 42;
	while (i < iterations) // 42 number of iterarions
	{
		z = sum_complex(distributive(z), c);
		if ((z.r * z.r) + (z.i * z.i) > 4)
		{
			color = pantograph(i, iterations, BLACK, WHITE);
			ft_mlx_pixel_put(&fractol->img, x, y, color);
			return ;
		}
		i++;
	}
	ft_mlx_pixel_put(&fractol->img, x, y, LAVA);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	offset;

	offset = (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)(data->addr + offset) = color;
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.r = z1.r + z2.r;
	result.i = z1.i + z2.i;
	return (result);
}

t_complex	distributive(t_complex z)
{
	t_complex	result;

	result.r = (z.r * z.r) - (z.i * z.i);
	result.i = 2 * z.r * z.i;
	return (result);
}
