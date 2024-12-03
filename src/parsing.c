/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:47:12 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/03 14:45:39 by thomarna         ###   ########.fr       */
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

void	init_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	if (ft_strncmp(fractal->name, "mandel", 6) == 0)
		calculate_mandel(fractal);
	if (ft_strncmp(fractal->name, "julia", 5) == 0)
		calculate_julia(fractal);
}

static int	ft_freesplit(char **split, int code)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (code);
}

int	parsing(t_fractal *fractal, char **av)
{
	char	**split;

	fractal->max = 500;
	fractal->ratio = (double)WIDTH / HEIGHT;
	split = ft_split(ft_sanitize(av), ' ');
	if (split[0] == NULL)
		return (ft_freesplit(split, 1));
	if (ft_strncmp(split[0], "julia", 5) == 0)
	{
		if (split[1] == NULL || split[2] == NULL)
			return (ft_freesplit(split, 1));
		else
		{
			fractal->cx = ft_atof(split[1]);
			fractal->cy = ft_atof(split[2]);
			fractal->name = "julia";
		}
	}
	else if (ft_strncmp(split[0], "mandel", 6) == 0)
		fractal->name = "mandel";
	else
		return (ft_freesplit(split, 1));
	return (ft_freesplit(split, 0));
}
