/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:37:45 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 17:53:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_food(t_fdf *fdf, t_sframe *s_frame)
{
	int			i;
	float		x;
	float		y;
	t_circle	c;

	i = 0;
	(void)fdf;
	while (i < FOOD)
	{
		x = s_frame->food_pos[i].x;
		y = s_frame->food_pos[i].y;
		init_circle_one(&c, x, y, s_frame->f_radius);
		init_circle_two(&c, 300, GREEN, DEF_COLOR);
		init_circle_three(&c, &fdf->b_ground);
		draw_circle_inward(&c, 0, 0.8, 4);
		i++;
	}
}

void	draw_enemies(t_fdf *fdf, t_sframe *sframe)
{
	int			i;
	float		x;
	float		y;
	t_circle	c;

	(void)fdf;
	i = 0;
	while (i < ENEM)
	{
		x = sframe->enemy[i].center.x;
		y = sframe->enemy[i].center.y;
		init_circle_one(&c, x, y, sframe->enemy[i].radius);
		init_circle_two(&c, 1000, sframe->enemy[i].center.color, DEF_COLOR);
		init_circle_three(&c, &fdf->b_ground);
		draw_circle_inward(&c, 0, 0.8, 4);
		i++;
	}
}

void	draw_snake(t_fdf *fdf, t_snake *snake, t_sframe *s_frame)
{
	float		x;
	float		y;
	t_circle	c;

	(void)fdf;
	x = (snake)->self_pos.x;
	y = (snake)->self_pos.y;
	init_circle_one(&c, x, y, s_frame->s_radius);
	init_circle_two(&c, 200, DEF_COLOR_MIN, DEF_COLOR);
	init_circle_three(&c, &fdf->b_ground);
	draw_circle_inward(&c, 0, 0.8, 4);
	snake = snake->next;
	while (snake)
	{
		x = (snake)->self_pos.x;
		y = (snake)->self_pos.y;
		init_circle_one(&c, x, y, s_frame->s_radius);
		init_circle_two(&c, 200, DEF_COLOR_MAX, DEF_COLOR);
		init_circle_three(&c, &fdf->b_ground);
		draw_circle_inward(&c, 0, 0.8, 4);
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
	my_mlx_putimg(fdf);
}
