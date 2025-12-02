/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:24:13 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/02 09:40:55 by gabrgarc         ###   ########.fr       */
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
	printf("./fractol mandelbrot\n./fractol julia <real> <imaginary>\n");
	printf("./fractol julia 0.285 0.01\n");
	printf("./fractol julia -0.70176 -0.3842\n");
	exit (0);
}
