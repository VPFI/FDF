/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:37:45 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:23:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_food(t_fdf *fdf, t_sframe *s_frame)
{
	int	i;

	i = 0;
	while (i < FOOD)
	{
		draw_circle_inward(s_frame->food_pos[i].x, s_frame->food_pos[i].y, s_frame->f_radius, 0, 300, GREEN, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		i++;
	}
}

void	draw_enemies(t_fdf *fdf, t_sframe *sframe)
{
	int	i;

	i = 0;
	while (i < ENEM)
	{
		draw_circle_inward(sframe->enemy[i].center.x, sframe->enemy[i].center.y, sframe->enemy[i].radius, 0, 1000, sframe->enemy[i].center.color, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		i++;
	}
}

void	draw_snake(t_fdf *fdf, t_snake *snake, t_sframe *s_frame)
{
	draw_circle_inward((snake)->self_pos.x, (snake)->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MIN, DEF_COLOR, 0.8, &fdf->b_ground, 4);
	snake = snake->next;
	while (snake)
	{
		draw_circle_inward(snake->self_pos.x, snake->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MAX, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		snake = snake->next;
	}
}

void	refresh_snake(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	populate_food(&fdf->s_frame);
	draw_food(fdf, &fdf->s_frame);
	draw_snake(fdf, fdf->snake, &fdf->s_frame);
	draw_enemies(fdf, &fdf->s_frame);
	write_score(fdf);
	if (check_col_snake(fdf, fdf->snake))
		snake_game_over(fdf);
	else if (enem_check_col_snake(fdf, fdf->snake, &fdf->s_frame))
		snake_game_over(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}
