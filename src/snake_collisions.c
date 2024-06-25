/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:30:25 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:03:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_col_snake(t_fdf *fdf, t_snake *snk)
{
	t_coords	head;
	int			diff;

	diff = 0;
	head = snk->self_pos;
	snk = snk->next;
	while (snk)
	{
		diff = fabs(head.x - snk->self_pos.x) + fabs(head.y - snk->self_pos.y);
		if (diff < (fdf->s_frame.s_radius * 2))
		{
			return (1);
		}
		snk = snk->next;
	}
	return (0);
}

int	check_col_food(t_snake *snake, t_sframe *sf)
{
	t_coords	hd;
	int			diff;
	int			i;

	i = 0;
	diff = 0;
	hd = snake->self_pos;
	while (i < FOOD)
	{
		diff = fabs(hd.x - sf->food_pos[i].x) + fabs(hd.y - sf->food_pos[i].y);
		if (diff < ((sf->f_radius + sf->s_radius)))
		{
			sf->food_pos[i].x = -1000;
			sf->food_pos[i].y = -1000;
			sf->score++;
			sf->food--;
			return (1);
		}
		i++;
	}
	return (0);
}

void	enem_check_col_food(t_sframe *sframe)
{
	int		diff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	diff = 0;
	while (j < ENEM)
	{
		i = 0;
		while (i < FOOD)
		{
			diff = fabs(sframe->enemy[j].center.x - sframe->food_pos[i].x)
				+ fabs(sframe->enemy[j].center.y - sframe->food_pos[i].y);
			if (diff < (sframe->f_radius + sframe->enemy->radius))
			{
				sframe->food_pos[i].x = -1000;
				sframe->food_pos[i].y = -1000;
				sframe->enemy[j].radius += 10;
				sframe->food--;
			}
			i++;
		}
		j++;
	}
}

int	enem_check_col_snake(t_fdf *fdf, t_snake *snake, t_sframe *sframe)
{
	t_coords	head;
	int			diff;
	int			i;

	i = 0;
	diff = 0;
	head = snake->self_pos;
	while (i < ENEM)
	{
		diff = fabs(sframe->enemy[i].center.x - snake->self_pos.x)
			+ fabs(sframe->enemy[i].center.y - snake->self_pos.y);
		if (diff < ((sframe->enemy[i].radius + sframe->s_radius)))
		{
			snake_game_over(fdf);
			return (1);
		}
		i++;
	}
	return (0);
}
