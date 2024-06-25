/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:19:42 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 20:46:34 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_scene_four(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_inward(CENTER_X, CENTER_Y, 1500, 0, 1000, WHITE, BLACK, 0.7, &fdf->b_ground, 4);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 350, BLACK, CYAN_GULF, 0.85, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_five(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 510, 1300, 900, ORANGE_GULF, ORANGE_GULF, 1, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 400, CYAN_GULF, CYAN_GULF, 1, &fdf->b_ground, 4);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 510, 4000, BLACK, ORANGE_GULF, 0.03, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 500, 490, 4000, BLACK, CYAN_GULF, 0.03, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}