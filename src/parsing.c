/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:47:12 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/02 20:48:29 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static char	*ft_sanitize(char **av)
{
	char	**start;

	start = ++av;
	while (*(av + 1))
	{
		(*av)[ft_strlen(*av)] = ' ';
		av++;
	}
	return (*start);
}

int	parsing(t_fractal *fractal, char **av)
{
	char **split;

	fractal->max = 300;
	fractal->ratio = (double) WIDTH / HEIGHT;
	split = ft_split(ft_sanitize(av), ' ');
	if (ft_strncmp(split[0], "julia", 5) == 0)
	{
		if (split[1] == NULL || split[2] == NULL)
			return (1);
		else
		{
			fractal->cx = ft_atof(split[1]);
			fractal->cy = ft_atof(split[2]);
		}
		calculate_julia(fractal);
	}
	else if (ft_strncmp(split[0], "mandel", 7) == 0)
		calculate_mandel(fractal);
	else
		return (1);
	return (0);
}
