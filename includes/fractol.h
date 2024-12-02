/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:41:58 by thomarna          #+#    #+#             */
/*   Updated: 2024/12/02 20:27:43 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <SDL2/SDL_mouse.h>
# include <float.h>

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# ifndef DOUBLE_MAX
#  define DOUBLE_MAX
# endif

typedef struct s_mlx
{
	void	*con;
	void	*win;
	void	*img;
}			t_mlx;

typedef struct s_fractal
{
	char	*name;
	t_mlx	mlx;
	double	zoom;
	int		x;
	int		y;
	double	cx;
	double	cy;
	double	zx;
	double	zy;
	int		max;
	double	ratio;
}			t_fractal;

int			parsing(t_fractal *fractal, char **av);
void		calculate_mandel(t_fractal *fractal);
void		calculate_julia(t_fractal *fractal);
int			message(void);
#endif
