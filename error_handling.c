/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:24:13 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/07 17:34:51 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_error(void *ptr, int errum)
{
	free(ptr);
	error_manager(errum);
}

void	mlx_error(t_fractol *mlx, char *s)
{
	if (mlx->img.layer)
		mlx_destroy_image(mlx->connection, mlx->img.layer);
	if (mlx->win)
		mlx_destroy_window(mlx->connection, mlx->win);
	if (mlx->connection)
	{
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
	}
	ft_printf("Error: %s.\n", s);
	exit(1);
}

void	error_manager(int errnum)
{
	if (errnum == EINVAL)
		ft_printf("Error: %s\n", strerror(errnum));
	if (errnum == EINVNU)
		ft_printf("Error: Invalid numbers of arguments.\n");
	if (errnum == EINVNA)
		ft_printf("Error: Invalid name.\n");
	ft_printf("./fractol mandelbrot\n./fractol julia <real> <imaginary>\n");
	ft_printf("./fractol julia 0.285 0.01\n");
	ft_printf("./fractol julia -0.8 0.156\n");
	exit (0);
}
