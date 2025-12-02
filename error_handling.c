/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:24:13 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/02 10:09:18 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_error(void *ptr, int errum)
{
	free(ptr);
	error_manager(errum);
}

void	error_manager(int errnum)
{
	char	*error_str;

	error_str = strerror(errnum);
	perror(error_str);
	ft_printf("./fractol mandelbrot\n./fractol julia <real> <imaginary>\n");
	ft_printf("./fractol julia 0.285 0.01\n");
	ft_printf("./fractol julia -0.8 0.156\n");
	exit (0);
}
