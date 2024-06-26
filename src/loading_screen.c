/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:16:43 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 18:25:02 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_param_loading(t_fdf *fdf, float *fade, int *color_comp, int *color)
{
	fade[0] = (float)((r_color(BLACK)) - (r_color(DEF_COLOR_MAX))) / 180;
	fade[1] = (float)((g_color(BLACK)) - (g_color(DEF_COLOR_MAX))) / 180;
	fade[2] = (float)((b_color(BLACK)) - (b_color(DEF_COLOR_MAX))) / 180;
	color_comp[0] = r_color(DEF_COLOR_MAX) + (fade[0] * fdf->animation_steps);
	color_comp[1] = g_color(DEF_COLOR_MAX) + (fade[1] * fdf->animation_steps);
	color_comp[2] = b_color(DEF_COLOR_MAX) + (fade[2] * fdf->animation_steps);
	*color = trgb_color(0, color_comp[0], color_comp[1], color_comp[2]);
}

void	loading_animation(t_fdf *fdf)
{
	int			color;
	float		fade[3];
	int			color_comp[3];
	t_circle	c;

	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	color = BLACK;
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	set_param_loading(fdf, fade, color_comp, &color);
	init_circle_one(&c, CENTER_X, CENTER_Y - 100, 400);
	init_circle_two(&c, 3000, color, BLACK);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 0, 0.8, 4);
	init_circle_one(&c, CENTER_X, CENTER_Y - 100, 400);
	init_circle_two(&c, 3000, CYAN_GULF, BLACK);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_outward(&c, 410, 0.03);
	animation_write(fdf);
	my_mlx_putimg(fdf);
	if (fdf->animation_steps == 180)
		fdf->increment = -1;
	if (fdf->animation_steps == 0)
		fdf->increment = 1;
	fdf->animation_steps += fdf->increment;
}

void	draw_loading_screen(t_fdf *fdf, float perc)
{
	t_circle	c1;
	t_circle	c2;

	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_circle_one(&c1, CENTER_X, CENTER_Y - 100, 400);
	init_circle_two(&c1, 3000, CYAN_GULF, BLACK);
	init_circle_three(&c1, &fdf->b_ground);
	draw_circle_outward(&c1, 410, 0.03);
	init_circle_one(&c2, CENTER_X, CENTER_Y - 100, 400);
	init_circle_two(&c2, 3000, CYAN_GULF, BLACK);
	init_circle_three(&c2, &fdf->b_ground);
	draw_circle_loading(&c2, 0, 0.7, perc);
	loading_write(fdf);
	my_mlx_putimg(fdf);
	if (perc == 1)
		fdf->load_flag = 1;
}
