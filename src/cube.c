/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:19:42 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:22:06 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	scale_cube(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		cube->coord[i].x = (WINW * 0.05) + (cube->pad * cube->coord[i].x);
		cube->coord[i].y = (WINH * 0.075) + (cube->pad * cube->coord[i].y);
		i++;
	}
}

void	rotate_cube(t_fdf *fdf, t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		rotate_x(&cube->coord[i], (fdf->rot_deg[X] * PI / 180));
		rotate_y(&cube->coord[i], (fdf->rot_deg[Y] * PI / 180));
		rotate_z(&cube->coord[i], (fdf->rot_deg[Z] * PI / 180));
		i++;
	}
}

void	reset_cube(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		cube->coord[i] = cube->coord_backup[i];
		i++;
	}
}

void	get_backup_cube(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		cube->coord_backup[i] = cube->coord[i];
		i++;
	}
}

void	init_cube(t_cube *cube)
{
	int	i;

	i = 0;
	cube->pad = 80;
	while (i < 8)
	{
		cube->coord[i].x = 0.5;
		cube->coord[i].y = 0.5;
		cube->coord[i].z = 0.5;
		cube->coord[i].color = GRAY_LIGHT;
		i++;
	}
	cube->coord[0].x = -0.5;
	cube->coord[0].y = -0.5;
	cube->coord[0].z = -0.5;
	cube->coord[1].y = -0.5;
	cube->coord[1].z = -0.5;
	cube->coord[2].z = -0.5;
	cube->coord[3].x = -0.5;
	cube->coord[3].z = -0.5;
	cube->coord[4].x = -0.5;
	cube->coord[4].y = -0.5;
	cube->coord[5].y = -0.5;
	cube->coord[7].x = -0.5;
	get_backup_cube(cube);
}
