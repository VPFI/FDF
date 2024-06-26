/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:53:49 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 19:31:14 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_fdf(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINW, WINH, "FDF");
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_cube(&fdf->cube);
	fdf->mouse_delayer = 3;
	fdf->zoom = 0.7;
	fdf->z_factor = 1;
	fdf->increment = 1;
}

void	init_circle_one(t_circle *circle, float x, float y, int radius)
{
	circle->center_x = x;
	circle->center_y = y;
	circle->radius = radius;
}

void	init_circle_two(t_circle *circle, float smth, int color1, int color2)
{
	circle->smoothness = smth;
	circle->og_color = color1;
	circle->fin_color = color2;
}

void	init_circle_three(t_circle *circle, t_img *img)
{
	circle->img = img;
}

void	init_vars(int *j, int *aux, char ***temp)
{
	*j = 0;
	*aux = 0;
	*temp = NULL;
}
