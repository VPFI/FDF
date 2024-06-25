/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:16:43 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 20:55:59 by vperez-f         ###   ########.fr       */
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
	int		color;
	float	fade[3];
	int		color_comp[3];
	
	if (fdf->b_ground.img_ptr)
			mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	color = BLACK;
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	set_param_loading(fdf, fade, color_comp, &color);
	draw_circle_inward(CENTER_X, CENTER_Y - 100, 400, 0, 3000, color, BLACK, 0.8, &fdf->b_ground, 4);
	draw_circle_outward(CENTER_X, CENTER_Y - 100, 400, 410, 3000, CYAN_GULF, BLACK, 0.03, &fdf->b_ground);
	write_str(fdf, "ENT", WINW * 0.43, WINH * 0.819, 3);
	write_str(fdf, "ER", WINW * 0.513, WINH * 0.819, 3);
	write_str(fdf, ">>>", WINW * 0.458, WINH * 0.877, 3);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	if (fdf->animation_steps == 180)
		fdf->increment = -1;
	if (fdf->animation_steps == 0)
		fdf->increment = 1;
	fdf->animation_steps += fdf->increment;
}

void	draw_loading_screen(t_fdf *fdf, float perc)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y - 100, 400, 410, 3000, CYAN_GULF, BLACK, 0.03, &fdf->b_ground);
	draw_circle_loading(CENTER_X, CENTER_Y - 100, 400, 0, 3000, CYAN_GULF, BLACK, 0.7, &fdf->b_ground, perc);
	write_str(fdf, "LOADI", WINW * 0.4, WINH * 0.819, 3);
	write_str(fdf, "NG", WINW * 0.533, WINH * 0.819, 3);
	write_str(fdf, "---", WINW * 0.458, WINH * 0.877, 3);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	if (perc == 1)
		fdf->load_flag = 1;
}