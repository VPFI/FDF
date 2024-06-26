/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:19:42 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 20:07:46 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_scene_four(t_fdf *fdf)
{
	t_circle	c;

	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_circle_one(&c, CENTER_X, CENTER_Y, 1500);
	init_circle_two(&c, 1000, WHITE, BLACK);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 0, 0.7, 4);
	init_circle_one(&c, CENTER_X, CENTER_Y, 490);
	init_circle_two(&c, 350, BLACK, CYAN_GULF);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 0, 0.85, 4);
	my_mlx_putimg(fdf);
}

void	draw_scene_five(t_fdf *fdf)
{
	t_circle	c;

	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_circle_one(&c, CENTER_X, CENTER_Y, 510);
	init_circle_two(&c, 900, ORANGE_GULF, ORANGE_GULF);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_outward(&c, 1300, 1);
	init_circle_one(&c, CENTER_X, CENTER_Y, 490);
	init_circle_two(&c, 400, CYAN_GULF, CYAN_GULF);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 0, 1, 4);
	init_circle_one(&c, CENTER_X, CENTER_Y, 500);
	init_circle_two(&c, 4000, BLACK, ORANGE_GULF);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_outward(&c, 510, 0.03);
	init_circle_one(&c, CENTER_X, CENTER_Y, 500);
	init_circle_two(&c, 4000, BLACK, CYAN_GULF);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 490, 0.03, 4);
	my_mlx_putimg(fdf);
}
