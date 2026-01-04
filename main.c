/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/04 18:12:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mlx_connection(t_fractol *mlx);
static void	fractol_init(t_fractol *fractol);

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		error_manager(EINVNU);
	fractol.name = NULL;
	if (!ft_strncmp(argv[1], "Mandelbrot", 11) && argc == 2)
		fractol.name = "Mandelbrot";
	if (!ft_strncmp(argv[1], "Julia", 6) && argc == 4)
	{
		fractol.name = "Julia";
		input_validations(&argv[2], &fractol);
	}
	if (fractol.name == NULL)
		error_manager(EINVNA);
	mlx_connection(&fractol);
	fractol_init(&fractol);
	fractol_render(&fractol);
	mlx_loop(fractol.connection);
	return (0);
}

static void	mlx_connection(t_fractol *mlx)
{
	mlx->connection = mlx_init();
	if (!mlx->connection)
		mlx_error(mlx, "Connection could not be established");
	mlx->win = mlx_new_window(mlx->connection, width, height, mlx->name);
	if (!mlx->win)
		mlx_error(mlx, "it was not possible to create a window");
	mlx->img.layer = mlx_new_image(mlx->connection, width, height);
	if (!mlx->img.layer)
		mlx_error(mlx, "It was not possible to create an image layer");
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
	fractol->zoom = 1.0;
}
