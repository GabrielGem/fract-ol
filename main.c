/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/29 18:27:28 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		return (0);
	fractol.name = NULL;
	if (!ft_strncmp(argv[1], "mandelbrot", 11) && argc == 2)
		fractol.name = "mandelbrot";
	if (!ft_strncmp(argv[1], "julia", 6) && argc == 4)
	{
		fractol.name = "julia";
		fractol.k.r = atof(argv[2]);
		fractol.k.i = atof(argv[3]);
	}
	if (fractol.name == NULL) // message with suggestion the arguments
		return (0);
	mlx_connection(&fractol);
	fractol_init(&fractol);
	fractol_render(&fractol);
	mlx_loop(fractol.connection);
	return (0);
}

void	mlx_connection(t_fractol *mlx)
{
	mlx->connection = mlx_init();
	mlx->win = mlx_new_window(mlx->connection, WIDTH, HEIGHT, mlx->name);
	mlx->img.layer = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.layer, &mlx->img.bpp, &mlx->img.line_len, &mlx->img.endian);
	event_manager(mlx);
}

void	fractol_init(t_fractol *fractol)
{
	fractol->range.min.r = -2.0;
	fractol->range.min.i = -2.0;
	fractol->range.max.r = 2.0;
	fractol->range.max.i = 2.0;
	fractol->axis.x = 0.0; 
	fractol->axis.y = 0.0;
	fractol->zoom = 1.0;
}

void	fractol_render(t_fractol *fractol)
{
	int			x;
	int			y;
	int			*pixel_ptr;
	int			out;

	pixel_ptr = (int *)fractol->img.addr;
	fractol->coordinates.r = (fractol->range.max.r - (fractol->range.min.r)) / WIDTH;
	fractol->coordinates.i = (fractol->range.min.i - fractol->range.max.i) / HEIGHT;
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
	mlx_put_image_to_window(fractol->connection, fractol->win, fractol->img.layer, 0, 0);
}

int	handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	t_complex	pixel;
	double		temp_real;
	int			i;

	pixel.r = fractol->range.min.r + (x * fractol->coordinates.r);
	pixel.i = fractol->range.max.i + (y * fractol->coordinates.i);
	if (fractol->name[0] == 'm')
	{
		z = (t_complex){0.0, 0.0};
		c = pixel;
	}
	if (fractol->name[0] == 'j')
	{
		z = pixel;
		c = fractol->k;
	}
	i = 0;
	while (i < ITERATIONS)
	{
		if ((z.r * z.r) + (z.i * z.i) > 4.0)
			return (i);
		temp_real = ((z.r * z.r) - (z.i * z.i)) + c.r;
		z.i = (2 * z.r * z.i) + c.i;
		z.r = temp_real;
		i++;
	}
	return (ITERATIONS);
}
