/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:41:18 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/02 20:32:28 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <string.h>

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

void redraw(t_fractal *fractal)
{
	if (strncmp(fractal->name, "mandel", 6) == 0)
		calculate_mandel(fractal);
	if (strncmp(fractal->name, "julia", 5) == 0)
		calculate_julia(fractal);
}

int wheel_hook(int event, void* param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	(void)(fractal);
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

int	message()
{
	ft_printf("\\o/ Fractol \\o/\n");
	ft_printf("Usage:\n");
	ft_printf("- Mandelbrot: ./fractol mandel\n");
	ft_printf("- Julia: ./fractol julia <arg1> <arg2>\n");
	return (0);
}

void	exit_fractal(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx.con, fractal->mlx.win);
	mlx_destroy_display(fractal->mlx.con);
	free(fractal);
}

int	main(int ac, char **av)
{
	t_fractal *fractal;
	t_mlx mlx;

	if (ac < 2)
		return (message());
	fractal = malloc(sizeof(t_fractal));
	if (fractal == NULL)
		return (0);
	mlx.con = mlx_init();
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractol");
	fractal->mlx = mlx;
	fractal->zoom = 1.0;
	mlx_set_fps_goal(mlx.con, 10);
	mlx_on_event(mlx.con, mlx.win, MLX_WINDOW_EVENT, window_hook, fractal);
	mlx_on_event(mlx.con, mlx.win, MLX_MOUSEWHEEL, wheel_hook, fractal);
	mlx_on_event(mlx.con, mlx.win, MLX_KEYDOWN, key_hook, fractal);
	if (parsing(fractal, av))
	{
		exit_fractal(fractal);
		return (message());
	}
	mlx_loop(mlx.con);
	exit_fractal(fractal);
}
