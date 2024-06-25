/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:46:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 18:55:45 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	populate_food(t_sframe *s_frame)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	if (0 < s_frame->food)
		return ;
	s_frame->food = FOOD;
	while (i < s_frame->food)
	{
		x = rand() % WINW - 10;
		y = rand() % WINH - 10;
		s_frame->food_pos[i].x = x;
		s_frame->food_pos[i].y = y;
		i++;
	}
}

void	set_enemies(t_sframe *sframe)
{
	sframe->enemy[0].center.x = WINW * 0.25;
	sframe->enemy[0].center.y = WINH * 0.25;
	sframe->enemy[0].center.color = RED;
	sframe->enemy[0].radius = 80;
	sframe->enemy[1].center.x = WINW * 0.75;
	sframe->enemy[1].center.y = WINH * 0.25;
	sframe->enemy[1].center.color = PINK;
	sframe->enemy[1].radius = 80;
}

void	start_snake(t_fdf *fdf)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = CENTER_X;
	y = CENTER_Y;
	while (i < 30)
	{
		add_body(&fdf->snake, new_body(x + (i * (20.5 * 2)), y, 0, 0));
		i++;
	}
}

void	init_snake(t_fdf *fdf)
{
	int		i;

	i = 0;
	if (fdf->snake_flag == 1)
		snake_lstclear(&fdf->snake);
	fdf->snake = NULL;
	start_snake(fdf);
	fdf->snake_flag = 1;
	fdf->s_frame.s_radius = 20;
	fdf->s_frame.dir = 0;
	fdf->s_frame.food = 0;
	fdf->s_frame.f_radius = 20;
	fdf->s_frame.s_delayer = 1;
	fdf->s_frame.score = 0;
	set_enemies(&fdf->s_frame);
	refresh_snake(fdf);
}
