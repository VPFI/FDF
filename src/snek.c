/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:46:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/21 20:17:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	snake_lstclear(t_snake **lst)
{
	t_snake	*temp;
	
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
	}
}

t_snake	*snake_last(t_snake	*lst)
{
	if (lst)
	{
		if (lst->next)
			return (snake_last(lst->next));
	}
	return (lst);
}

t_snake	*new_body(int x1, int y1, int x2, int y2)
{
	t_snake	*res;

	res = (t_snake *)malloc(sizeof(t_snake));
	if (!res)
		return (NULL);
	res->self_pos.x = x1;
	res->self_pos.y = y1;
	res->prev_pos.x = x2;
	res->prev_pos.y = y2;
	res->next = NULL;
	return (res);
}

void	add_body(t_snake **lst, t_snake *new)
{
	t_snake	*last_entry;

	if (lst)
	{
		if (*lst)
		{
			last_entry = snake_last(*lst);
			last_entry->next = new;
		}
		else
			*lst = new;
	}
}

void	draw_snake(t_fdf *fdf, t_snake *snake, t_sframe *s_frame)
{
	draw_circle_inward((snake)->self_pos.x, (snake)->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MIN, DEF_COLOR, 0.8, &fdf->b_ground, 4);
	(snake) = (snake)->next;
	while(snake)
	{
		draw_circle_inward((snake)->self_pos.x, (snake)->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MAX, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		(snake) = (snake)->next;
	}
}
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

int	check_col_snake(t_fdf *fdf, t_snake *snake)
{
	t_coords head;
	int		diff;

	diff = 0;
	head = snake->self_pos;
	snake = snake->next;
	while (snake)
	{
		diff = fabs(head.x - snake->self_pos.x) + fabs(head.y - snake->self_pos.y);
		if (diff < (fdf->s_frame.s_radius * 2))
		{
			return (1);
		}
		snake = snake->next;
	}
	return (0);
}
void	write_score(t_fdf *fdf)
{
	char *score;

	score = ft_itoa(fdf->s_frame.score);
	write_str(fdf, "SCORE", WINW * 0.8, WINH * 0.05, 7);
	if (fdf->s_frame.score < 10)
	{
		write_str(fdf, score, WINW * 0.87, WINH * 0.1, 7);
		write_str(fdf, "0", WINW * 0.855, WINH * 0.1, 7);
	}
	else
		write_str(fdf, score, WINW * 0.845, WINH * 0.1, 7);
	free(score);
}

void	snake_game_over(t_fdf *fdf)
{
	snake_lstclear(&fdf->snake);
	write_str(fdf, "GAME", CENTER_X - 270, CENTER_Y, 3);
	write_str(fdf, "OVER", CENTER_X + 40, CENTER_Y, 3);
	fdf->snake_flag = 0;
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
			diff = fabs(sframe->enemy[j].center.x - sframe->food_pos[i].x) + fabs(sframe->enemy[j].center.y - sframe->food_pos[i].y);
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

int	check_col_food(t_snake *snake, t_sframe *sframe)
{
	t_coords head;
	int		diff;
	int		i;

	i = 0;
	diff = 0;
	head = snake->self_pos;
	while (i < FOOD)
	{
		diff = fabs(head.x - sframe->food_pos[i].x) + fabs(head.y - sframe->food_pos[i].y);
		if (diff < ((sframe->f_radius + sframe->s_radius)))
		{
			sframe->food_pos[i].x = -1000;
			sframe->food_pos[i].y = -1000;
			sframe->score++;
			sframe->food--;
			return (1);
		}
		i++;
	}	
	return (0);
}

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

void	get_enem_target(t_fdf *fdf, t_sframe *sframe)
{
	int		diff;
	int		target_food;
	int		target_dist;
	int		i;
	int		j;

	j = 1;
	diff = 0;
	target_food = 0;
	sframe->enemy[0].target_pos = fdf->snake->self_pos;
	while (j < ENEM)
	{
		i = 0;
		target_dist = 100000;
		while (i < FOOD)
		{
			diff = fabs(sframe->enemy[j].center.x - sframe->food_pos[i].x) + fabs(sframe->enemy[j].center.x - sframe->food_pos[i].y);
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

int	enem_check_col_snake(t_fdf *fdf, t_snake *snake, t_sframe *sframe)
{
	t_coords head;
	int		diff;
	int		i;

	i = 0;
	diff = 0;
	head = snake->self_pos;
	while (i < ENEM)
	{
		diff = fabs(sframe->enemy[i].center.x - snake->self_pos.x) + fabs(sframe->enemy[i].center.y - snake->self_pos.y);
		if (diff < ((sframe->enemy[i].radius + sframe->s_radius)))
		{
			snake_game_over(fdf);
			return (1);
		}
		i++;
	}
	return (0);
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
		if ( x_inc < 0)
			x_inc = (x_inc / x_inc) * (-1);
		else
			x_inc = (x_inc / x_inc);
		if (y_inc < 0)
			y_inc = (y_inc / y_inc) * (-1);
		else
			y_inc = (y_inc / y_inc);
		if (sframe->enemy[i].center.x != sframe->enemy[i].target_pos.x)
			sframe->enemy[i].center.x += (x_inc * 7);
		if (sframe->enemy[i].center.y != sframe->enemy[i].target_pos.y)
			sframe->enemy[i].center.y += (y_inc * 7);
		i++;
	}
	enem_check_col_food(sframe);
}
void	draw_enemies(t_fdf *fdf, t_sframe *sframe)
{
	int i;

	i = 0;
	while (i < ENEM)
	{
		draw_circle_inward(sframe->enemy[i].center.x, sframe->enemy[i].center.y, sframe->enemy[i].radius, 0, 1000, sframe->enemy[i].center.color, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		i++;
	}
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

void	start_snake(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < 30)
	{
		add_body(&fdf->snake, new_body(CENTER_X + (i * (20.5 * 2)), CENTER_Y, 0, 0));
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
	//sframe->enemy[2].center.x = WINW * 0.5;
	//sframe->enemy[2].center.y = WINH * 0.75;
	//sframe->enemy[2].center.color = RED;
	//sframe->enemy[2].radius = 80;
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