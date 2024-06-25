/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:06:20 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 20:18:29 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	reset_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_size)
	{
		fdf->map[i].x = fdf->backup_map[i].x;
		fdf->map[i].y = fdf->backup_map[i].y;
		fdf->map[i].z = fdf->backup_map[i].z * fdf->z_factor;
		i++;
	}
}

void	scale_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->spacing_W = (WINW * fdf->zoom) / (fdf->map_edges_W);
	fdf->spacing_H = (WINH * fdf->zoom) / (fdf->map_edges_H);
	while (i < fdf->map_size)
	{
		fdf->map[i].x = (CENTER_X) + (fdf->spacing_W * fdf->map[i].x) + fdf->tras[X];
		fdf->map[i].y = (CENTER_Y) + (fdf->spacing_H * fdf->map[i].y) + fdf->tras[Y];
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_coords i_pt;
	t_coords f_pt;

	int i = 0;
	int j = 0;
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	while (j < fdf->map_edges_H)
	{
		while ((i % fdf->map_W) < fdf->map_edges_W)
		{
			i_pt = fdf->map[i];
			f_pt = fdf->map[i + 1];
			init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
			f_pt = fdf->map[i + fdf->map_W];
			init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
			i++;
		}
		i_pt = fdf->map[i];
		f_pt = fdf->map[i + fdf->map_W];
		init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
		i++;
		j++;
	}
	while ((i % fdf->map_W) < fdf->map_edges_W)
	{
		i_pt = fdf->map[i];
		f_pt = fdf->map[i + 1];
		init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
		i++;
	}
	draw_cube(fdf);
	write_str(fdf, "FDF", WINW * 0.9, WINH * 0.06, 4);
	write_str(fdf, "_", WINW * 0.901, WINH * 0.06, 1);
	write_str(fdf, "42", WINW * 0.915, WINH * 0.14, 6);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}
