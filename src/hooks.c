/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:49:40 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/03 15:07:59 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	window_hook(int event, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (event == 0)
	{
		mlx_destroy_image(fractal->mlx.con, fractal->mlx.img);
		mlx_loop_end(fractal->mlx.con);
	}
	return (0);
}

int	key_hook(int key, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (key == 41)
	{
		mlx_destroy_image(fractal->mlx.con, fractal->mlx.img);
		mlx_loop_end(fractal->mlx.con);
	}
	return (0);
}

static void	redraw(t_fractal *fractal)
{
	if (ft_strncmp(fractal->name, "mandel", 6) == 0)
		calculate_mandel(fractal);
	if (ft_strncmp(fractal->name, "julia", 5) == 0)
		calculate_julia(fractal);
}

int	wheel_hook(int event, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (event == 1)
		fractal->zoom /= 1.10;
	if (event == 2)
		fractal->zoom *= 1.10;
	if (fractal->zoom < 0.1)
		fractal->zoom = 0.1;
	if (fractal->zoom > 10.0)
		fractal->zoom = 10.0;
	mlx_destroy_image(fractal->mlx.con, fractal->mlx.img);
	redraw(fractal);
	return (0);
}
