/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:15:11 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/11/25 16:26:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <sys/time.h>
# include "libft.h"

# define BLACK	0x000000
# define WHITE	0xFFFFFF
# define LAVA	0xFF3300

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
	void	*mlx;
	void	*mlx_win;
	char	*name_win;
	t_data	img;
}	t_fractol;

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

enum e_sizes
{
	WIDTH = 500,
	HEIGHT = 500
};

void		fractol_init(t_fractol *fractol);
double		pantograph(double unscaled, double old_max,
			double new_min, double new_max);
void		fractol_render(t_fractol *fractol);
void		handle_pixel(int x, int y, t_fractol *fractol);
void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	distributive(t_complex z);

#endif
