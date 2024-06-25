/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:21:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:00:43 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_color_cube(t_cube *cube, int a, int b)
{
	if (a == 0 && b == 1)
	{
		cube->coord[a].color = RED;
		cube->coord[b].color = RED;
	}
	else if (a == 3 && b == 0)
	{
		cube->coord[a].color = GREEN;
		cube->coord[b].color = GREEN;
	}
	else if (a == 0 && b == 4)
	{
		cube->coord[a].color = BLUE;
		cube->coord[b].color = BLUE;
	}
	else
	{
		cube->coord[a].color = GRAY_LIGHT;
		cube->coord[b].color = GRAY_LIGHT;
	}
}

void	bres_cube(t_fdf *fdf, t_cube *cb)
{
	int		i;
	int		aux;

	i = 0;
	aux = 1;
	while (i < 8)
	{
		if (i < 4)
			aux = aux % 4;
		else
			aux = (aux % 4) + 4;
		set_color_cube(cb, i, aux);
		init_bresenham_line(&fdf->b_ground, &cb->coord[i], &cb->coord[aux]);
		i++;
		aux++;
	}
	i = 0;
	while (i < 4)
	{
		set_color_cube(cb, i, i + 4);
		init_bresenham_line(&fdf->b_ground, &cb->coord[i], &cb->coord[i + 4]);
		i++;
	}
}

void	draw_cube(t_fdf *fdf)
{
	reset_cube(&fdf->cube);
	rotate_cube(fdf, &fdf->cube);
	scale_cube(&fdf->cube);
	bres_cube(fdf, &fdf->cube);
}
