/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:54:49 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/03 15:06:50 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandel(t_fractal *fractal)
{
	int		i;
	double	x;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = ((fractal->x - (double)WIDTH / 2) / (double)WIDTH
			* fractal->zoom * 3.5);
	fractal->cy = ((fractal->y - (double)HEIGHT / 2) / (double)HEIGHT
			* fractal->zoom * 3.5 / fractal->ratio);
	while (++i < fractal->max)
	{
		x = fractal->zx * fractal->zx - fractal->zy * fractal->zy + fractal->cx;
		fractal->zy = 2. * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = x;
		if ((fractal->zx * fractal->zx + fractal->zy * fractal->zy) >= 4.0)
			break ;
	}
	if (i == fractal->max)
		mlx_set_image_pixel(fractal->mlx.con, fractal->mlx.img, fractal->x,
			fractal->y, 0xFF000000);
	else
		mlx_set_image_pixel(fractal->mlx.con, fractal->mlx.img, fractal->x,
			fractal->y, 0xFFFFFFFF * i);
}

void	calculate_mandel(t_fractal *fractal)
{
	fractal->mlx.img = mlx_new_image(fractal->mlx.con, WIDTH, HEIGHT);
	while (fractal->x < WIDTH)
	{
		while (fractal->y < HEIGHT)
		{
			mandel(fractal);
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
