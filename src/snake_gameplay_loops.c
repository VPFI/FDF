/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_gameplay_loops.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:34:28 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:21:09 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	set_snake_dir(t_sframe *sframe, int dist, int dir)
{
	if (0 < dist && !dir)
	{
		if (sframe->dir == 2 || sframe->dir == 0)
			return (1);
		sframe->dir = 1;
	}
	else if (dist < 0 && !dir)
	{
		if (sframe->dir == 1)
			return (1);
		sframe->dir = 2;
	}
	if (0 < dist && dir)
	{
		if (sframe->dir == 4)
			return (1);
		sframe->dir = 3;
	}
	else if (dist < 0 && dir)
	{
		if (sframe->dir == 3)
			return (1);
		sframe->dir = 4;
	}
	return (0);
}

void	get_enem_target(t_fdf *fdf, t_sframe *sframe)
{
	int		diff;
	int		target_dist;
	int		i;
	int		j;

	j = 1;
	sframe->enemy[0].target_pos = fdf->snake->self_pos;
	while (j < ENEM)
	{
		i = 0;
		target_dist = 100000;
		while (i < FOOD)
		{
			diff = fabs(sframe->enemy[j].center.x - sframe->food_pos[i].x)
				+ fabs(sframe->enemy[j].center.x - sframe->food_pos[i].y);
			if (diff < target_dist)
			{
				target_dist = diff;
				sframe->enemy[j].target_pos = sframe->food_pos[i];
			}
			i++;
		}
		j++;
	}
}

void	move_enemies(t_fdf *fdf, t_sframe *sframe)
{
	int	i;
	int	x_inc;
	int	y_inc;

	i = 0;
	get_enem_target(fdf, sframe);
	while (i < ENEM)
	{
		x_inc = sframe->enemy[i].target_pos.x - sframe->enemy[i].center.x;
		y_inc = sframe->enemy[i].target_pos.y - sframe->enemy[i].center.y;
		x_inc = (x_inc / abs(x_inc));
		y_inc = (y_inc / abs(y_inc));
		if (sframe->enemy[i].center.x != sframe->enemy[i].target_pos.x)
			sframe->enemy[i].center.x += (x_inc * 7);
		if (sframe->enemy[i].center.y != sframe->enemy[i].target_pos.y)
			sframe->enemy[i].center.y += (y_inc * 7);
		i++;
	}
	enem_check_col_food(sframe);
}

void	move_snake(t_fdf *fdf, t_snake *snake, int dist, int dir)
{
	t_coords	aux;

	if (set_snake_dir(&fdf->s_frame, dist, dir))
		return ;
	aux = snake->self_pos;
	if (!dir)
		snake->self_pos.x = (int)(snake->self_pos.x + dist) % WINW;
	else if (dir)
		snake->self_pos.y = (int)(snake->self_pos.y + dist) % WINH;
	if (snake->self_pos.x < 0)
		snake->self_pos.x = WINW - 1;
	if (snake->self_pos.y < 0)
		snake->self_pos.y = WINH - 1;
	snake = snake->next;
	while (snake)
	{
		snake->prev_pos = aux;
		aux = snake->self_pos;
		snake->self_pos = snake->prev_pos;
		snake = snake->next;
	}
	move_enemies(fdf, &fdf->s_frame);
	if (check_col_food(fdf->snake, &fdf->s_frame))
		add_body(&fdf->snake, new_body(aux.x, aux.y, 0, 0));
	refresh_snake(fdf);
}

void	move_snake_loop(t_fdf *fdf, t_sframe *sframe)
{
	while (fdf->s_frame.s_delayer % 90000000)
		fdf->s_frame.s_delayer++;
	fdf->s_frame.s_delayer = 1;
	if (sframe->dir == 1)
		move_snake(fdf, fdf->snake, 40, 0);
	else if (sframe->dir == 2)
		move_snake(fdf, fdf->snake, -40, 0);
	else if (sframe->dir == 3)
		move_snake(fdf, fdf->snake, 40, 1);
	else if (sframe->dir == 4)
		move_snake(fdf, fdf->snake, -40, 1);
}
