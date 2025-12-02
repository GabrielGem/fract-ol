/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/01 17:44:53 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mlx_connection(t_fractol *mlx);
static void	fractol_init(t_fractol *fractol);

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		error_manager(EINVAL);
	fractol.name = NULL;
	if (!ft_strncmp(argv[1], "mandelbrot", 11) && argc == 2)
		fractol.name = "mandelbrot";
	if (!ft_strncmp(argv[1], "julia", 6) && argc == 4)
	{
		fractol.name = "julia";
		validations(&argv[2], &fractol);
	}
	if (fractol.name == NULL)
		error_manager(EINVAL);
	mlx_connection(&fractol);
	fractol_init(&fractol);
	fractol_render(&fractol);
	mlx_loop(fractol.connection);
	return (0);
}

static void	mlx_connection(t_fractol *mlx)
{
	mlx->connection = mlx_init();
	mlx->win = mlx_new_window(mlx->connection, WIDTH, HEIGHT, mlx->name);
	mlx->img.layer = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.layer, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	event_manager(mlx);
}

static void	fractol_init(t_fractol *fractol)
{
	fractol->range.min.r = -2.0;
	fractol->range.min.i = -2.0;
	fractol->range.max.r = 2.0;
	fractol->range.max.i = 2.0;
	fractol->axis.x = 0.0;
	fractol->axis.y = 0.0;
	fractol->zoom = 1.0;
}
