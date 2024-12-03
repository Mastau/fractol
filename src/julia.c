/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:47:05 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/02 19:39:22 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fractal *fractal)
{
	int		i;
	double	x;

	i = 0;
	fractal->zx = ((fractal->x - (double)WIDTH / 2) / (double)WIDTH
			* fractal->zoom * 3.5);
	fractal->zy = ((fractal->y - (double)HEIGHT / 2) / (double)HEIGHT
			* fractal->zoom * 3.5 / fractal->ratio);
	while (++i < fractal->max)
	{
		x = fractal->zx;
		fractal->zx = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2.0 * fractal->zy * x + fractal->cy;
		if (fractal->zx * fractal->zx + fractal->zy * fractal->zy >= 4.0)
			break ;
	}
	if (i == fractal->max)
		mlx_set_image_pixel(fractal->mlx.con, fractal->mlx.img, fractal->x,
			fractal->y, 0xFF0000FF);
	else
		mlx_set_image_pixel(fractal->mlx.con, fractal->mlx.img, fractal->x,
			fractal->y, (0xFFFFFFFF / fractal->max) * i);
}

void	calculate_julia(t_fractal *fractal)
{
	fractal->name = "julia";
	fractal->mlx.img = mlx_new_image(fractal->mlx.con, WIDTH, HEIGHT);
	while (fractal->x < WIDTH)
	{
		while (fractal->y < HEIGHT)
		{
			julia(fractal);
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
	fractal->x = 0;
	fractal->y = 0;
	mlx_put_image_to_window(fractal->mlx.con, fractal->mlx.win,
		fractal->mlx.img, 0, 0);
}
