/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:32 by vperez-f          #+#    #+#             */
/*   Updated: 2024/07/02 16:07:47 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	extrude(t_fdf *fdf, float dist)
{
	int	i;

	i = 0;
	fdf->z_factor *= dist;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
}

void	zoom_map(t_fdf *fdf, float amount)
{
	if (fdf->zoom < 0.05 && amount < 1)
		return ;
	if (50 < fdf->zoom && 1 < amount)
		return ;
	fdf->zoom *= amount;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
}

void	rotate_key(t_fdf *fdf, int angle_x, int angle_y, int angle_z)
{
	reset_map(fdf);
	rotate_map(fdf, angle_x, angle_y, angle_z);
	scale_map(fdf);
	draw_map(fdf);
}

void	swap_persp(t_fdf *fdf, int p)
{
	int	angle[3];

	fdf->entered = 1;
	set_angles(angle);
	angle[X] = -fdf->rot_deg[X];
	angle[Y] = -fdf->rot_deg[Y];
	angle[Z] = -fdf->rot_deg[Z];
	if (p == 2)
		angle[X] = 90 - fdf->rot_deg[X];
	if (p == 3)
	{
		angle[X] = 45 - fdf->rot_deg[X];
		angle[Z] = -15 - fdf->rot_deg[Z];
	}
	reset_map(fdf);
	rotate_map(fdf, angle[X], angle[Y], angle[Z]);
	scale_map(fdf);
	draw_map(fdf);
}

void	move_key(t_fdf *fdf, int dist, int dir)
{
	int	i;

	i = 0;
	if (0 < fdf->snake_flag)
	{
		dist *= 2;
		move_snake(fdf, fdf->snake, dist, dir);
		return ;
	}
	if (!dist)
		return ;
	while (i < fdf->map_size)
	{
		if (dir)
			fdf->map[i].y += dist;
		else if (!dir)
			fdf->map[i].x += dist;
		i++;
	}
	if (dir)
		fdf->tras[Y] += dist;
	else if (!dir)
		fdf->tras[X] += dist;
	draw_map(fdf);
}
