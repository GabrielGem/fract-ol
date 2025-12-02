/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:33:29 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/02 09:32:56 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	valid_arguments(char *str);
static void	empty_arguments(char **args);

void	validations(char **args, t_fractol *fractol)
{
	char	*str;

	empty_arguments(args);
	str = ft_revsplit(args, ' ');
	valid_arguments(str);
	free(str);
	fractol->k = (t_complex){0.0, 0.0};
	fractol->k.r = ft_atof(args[0]);
	fractol->k.i = ft_atof(args[1]);
	return ;
}

static void	empty_arguments(char **args)
{
	while (*args)
	{
		if (**args == '\0')
			error_manager(EINVAL);
		args++;
	}
}

static void	valid_arguments(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			number = 1;
		if (!(ft_isdigit(str[i]) || ft_issignal(str[i])
				|| str[i] == ' ' || str[i] == '.'))
			clear_error(str, EINVAL);
		if (ft_issignal(str[i]) && ft_issignal(str[i + 1]))
			clear_error(str, EINVAL);
		if (ft_issignal(str[i]) && !ft_isdigit(str[i + 1]))
			clear_error(str, EINVAL);
		if (str[i] == '.' && ft_issignal(str[i + 1]))
			clear_error(str, EINVAL);
		i++;
	}
	if (!number)
		clear_error(str, EINVAL);
}
