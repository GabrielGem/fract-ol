/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:15:11 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/16 14:38:50 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "ft_printf.h"

# define BLACK	0x000000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_axes
{
	double	x;
	double	y;
}	t_axes;

typedef struct s_range
{
	t_complex	min;
	t_complex	max;
}	t_range;

typedef struct s_data
{
	void	*layer;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_fractol
{
	void		*connection;
	void		*win;
	char		*name;
	t_data		img;
	t_range		range;
	t_complex	coordinates;
	t_axes		axis;
	t_complex	k;
	double		zoom;
}	t_fractol;

typedef union u_color
{
	unsigned int	number;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}	s_channels;
}	t_color;

enum e_sizes
{
	iterations = 250,
	width = 500,
	height = 500,
};

enum e_errnum
{
	EINVAL = 22,
	EINVNU = 0,
	EINVNA = 1,
};

// fractol
void	fractol_render(t_fractol *fractol);

// event handling
void	event_manager(t_fractol *fractol);

// error handling
void	clear_error(void *ptr, int errnum);
void	mlx_error(t_fractol *mlx, char *s);
void	error_manager(int errnum);
void	input_validations(char **args, t_fractol *fractol);

#endif
