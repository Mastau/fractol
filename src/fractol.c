/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:41:18 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/03 14:52:47 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

int	message(void)
{
	ft_printf("\\o/ Fractol \\o/\n");
	ft_printf("Usage:\n");
	ft_printf("- Mandelbrot: ./fractol mandel\n");
	ft_printf("- Julia: ./fractol julia <arg1> <arg2>\n");
	ft_printf("Example: ./fractol julia -0.7 0.27015\n");
	return (0);
}

static void	exit_fractal(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx.con, fractal->mlx.win);
	mlx_destroy_display(fractal->mlx.con);
	free(fractal);
}

int	main(int ac, char **av)
{
	t_fractal	*fractal;
	t_mlx		mlx;

	if (ac < 2)
		return (message());
	fractal = malloc(sizeof(t_fractal));
	if (fractal == NULL)
		return (0);
	if (parsing(fractal, av))
	{
		free(fractal);
		return (message());
	}
	mlx.con = mlx_init();
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractol");
	fractal->mlx = mlx;
	fractal->zoom = 1.0;
	mlx_set_fps_goal(mlx.con, 10);
	mlx_on_event(mlx.con, mlx.win, MLX_WINDOW_EVENT, window_hook, fractal);
	mlx_on_event(mlx.con, mlx.win, MLX_MOUSEWHEEL, wheel_hook, fractal);
	mlx_on_event(mlx.con, mlx.win, MLX_KEYDOWN, key_hook, fractal);
	init_fractal(fractal);
	mlx_loop(mlx.con);
	exit_fractal(fractal);
}
