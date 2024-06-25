/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:48:32 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:49:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	reset_pos(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_size)
	{
		fdf->map[i].x -= fdf->tras[X];
		fdf->map[i].y -= fdf->tras[Y];
		i++;
	}
	fdf->tras[X] = 0;
	fdf->tras[Y] = 0;
	draw_map(fdf);
}

void	reset_zoom(t_fdf *fdf)
{
	fdf->zoom = 0.7;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
}

void	reset_all(t_fdf *fdf)
{
	int		i;

	i = 0;
	set_z_scaling(fdf);
	while (i < fdf->map_size)
	{
		fdf->map[i].x -= fdf->tras[X];
		fdf->map[i].y -= fdf->tras[Y];
		i++;
	}
	fdf->tras[X] = 0;
	fdf->tras[Y] = 0;
	fdf->zoom = 0.7;
	swap_persp(fdf, 3);
}
