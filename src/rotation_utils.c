/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:40:23 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:06:47 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotate_x(t_coords *pt, float angle)
{
	float	temp_y;
	float	temp_z;

	if (!angle)
		return ;
	temp_y = pt->y;
	temp_z = pt->z;
	pt->y = (temp_y * cos(angle)) + (temp_z * (-sin(angle)));
	pt->z = (temp_y * sin(angle)) + (temp_z * cos(angle));
}

void	rotate_y(t_coords *pt, float angle)
{
	float	temp_x;
	float	temp_z;

	if (!angle)
		return ;
	temp_x = pt->x;
	temp_z = pt->z;
	pt->x = (temp_x * cos(angle)) + (temp_z * sin(angle));
	pt->z = (temp_x * (-sin(angle))) + (temp_z * cos(angle));
}

void	rotate_z(t_coords *pt, float angle)
{
	float	temp_x;
	float	temp_y;

	if (!angle)
		return ;
	temp_x = pt->x;
	temp_y = pt->y;
	pt->x = (temp_x * cos(angle)) + (temp_y * (-sin(angle)));
	pt->y = (temp_x * sin(angle)) + (temp_y * cos(angle));
}

void	rotate_map(t_fdf *fdf, int deg_x, int deg_y, int deg_z)
{
	int		i;
	float	angle_x;
	float	angle_y;
	float	angle_z;

	i = 0;
	fdf->rot_deg[X] = (fdf->rot_deg[X] + deg_x) % 360;
	fdf->rot_deg[Y] = (fdf->rot_deg[Y] + deg_y) % 360;
	fdf->rot_deg[Z] = (fdf->rot_deg[Z] + deg_z) % 360;
	angle_x = fdf->rot_deg[X] * PI / 180;
	angle_y = fdf->rot_deg[Y] * PI / 180;
	angle_z = fdf->rot_deg[Z] * PI / 180;
	while (i < fdf->map_size)
	{
		rotate_x(&fdf->map[i], angle_x);
		rotate_y(&fdf->map[i], angle_y);
		rotate_z(&fdf->map[i], angle_z);
		i++;
	}
}
